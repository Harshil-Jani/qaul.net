// Copyright (c) 2021 Open Community Project Association https://ocpa.ch
// This software is published under the AGPLv3 license.

//! # Chat Module
//! 
//! Send and receive chat messages

use libp2p::{
    PeerId,
};
use prost::Message;
use state::Storage;
use std::sync::RwLock;
use std::collections::BTreeMap;
use sled_extensions::{
    DbExt,
    bincode::Tree,
};

use super::messaging;
use super::messaging::proto;
use super::messaging::Messaging;
use crate::node::user_accounts::{UserAccount, UserAccounts}; 
use crate::connections::{
    lan::Lan,
    internet::Internet,
};
use crate::rpc::Rpc;
use crate::storage::database::DataBase;
use crate::router;
use crate::utilities::timestamp::Timestamp;

/// Import protobuf message definition generated by 
/// the rust module prost-build.
pub mod rpc_proto { include!("qaul.rpc.chat.rs"); }


/// mutable state of chat messages
static CHAT: Storage<RwLock<Chat>> = Storage::new();

/// chat references per user account
#[derive(Clone)]
pub struct ChatUser {
    // chat conversations sled data base tree
    pub overview: Tree<rpc_proto::ChatOverview>,
    // messages sled data base tree
    pub messages: Tree<rpc_proto::ChatMessage>,
    // message id => db key
    pub message_ids: Tree<Vec<u8>>,
}

/// qaul Chat storage and logic
pub struct Chat {
    // data base tree references accessible
    // by user account
    db_ref: BTreeMap< Vec<u8>, ChatUser>,
}

impl Chat {
    /// initialize chat module
    pub fn init() {
        // create chat state
        let chat = Chat {
            db_ref: BTreeMap::new(),
        };
        CHAT.set(RwLock::new(chat));
    }


    /// Save a new incoming Message
    /// 
    /// This function saves an incoming chat message in the data base
    pub fn save_incoming_message(user_id: &PeerId, 
        sender_id: &PeerId, 
        content: &Vec<u8>, 
        sent_at: u64, 
        conversation_id: &messaging::ConversationId, 
        message_id: &Vec<u8>,
        status: u32)-> bool 
    {
        // create timestamp
        let timestamp = Timestamp::get_timestamp();

        // get data base of user account
        let db_ref = Self::get_user_db_ref(user_id.clone());

        // check if message_id is already exist
        if db_ref.message_ids.contains_key(message_id).unwrap(){
            return true;
        }

        // check if group message
        let is_group = !(conversation_id.
            is_equal(&messaging::ConversationId::from_peers(user_id, sender_id).unwrap()));

        log::error!("save incomeming is_group={}", is_group);

        let overview;
        match Self::update_overview(user_id, sender_id, &db_ref, 
            &conversation_id.to_bytes(), timestamp, content, &sender_id.to_bytes(), is_group) {
            Ok(chat_overview) => overview = chat_overview,
            Err(e) => {
                log::error!("{}", e);
                return false;
            }
        }

        // create data base key
        let db_key = Self::get_db_key_from_vec(&conversation_id.to_bytes(), overview.last_message_index);

        // create chat message
        let chat_message = rpc_proto::ChatMessage {
            index: overview.last_message_index,
            sender_id: sender_id.to_bytes(),
            message_id: message_id.clone(),
            status,
            is_group,
            conversation_id: conversation_id.to_bytes(),
            sent_at,
            received_at: timestamp,
            content: content.clone(),
        };

        // save message in data base
        if let Err(e) = db_ref.messages.insert(db_key.clone(), chat_message) {
            log::error!("Error saving chat message to data base: {}", e);
        }
        // flush trees to disk
        if let Err(e) = db_ref.messages.flush() {
            log::error!("Error chat messages flush: {}", e);
        }

        //save message id in data base
        if let Err(e) = db_ref.message_ids.insert(message_id.clone(), db_key.clone()) {
            log::error!("Error saving chat messageid to data base: {}", e);
        }
        // flush trees to disk
        if let Err(e) = db_ref.message_ids.flush() {
            log::error!("Error chat message_ids flush: {}", e);
        }
        true
    }


    // send the message
    pub fn send(user_account: &UserAccount, chat_message: rpc_proto::ChatMessageSend) -> Result<Vec<u8>, String> {
        // create timestamp
        let timestamp = Timestamp::get_timestamp();
        
        // create receiver
        let receiver;
        match PeerId::from_bytes(&chat_message.conversation_id) {
            Ok(id) => receiver = id,
            Err(e) => return Err(e.to_string()),
        }

        let conversation_id = messaging::ConversationId::from_peers(&user_account.id, &receiver).unwrap();

        let message_id = Messaging::generate_message_id(&user_account.id);

        log::error!("send msg_id={}, conversation_id={}", bs58::encode(message_id.clone()).into_string(), conversation_id.to_base58());
        // pack message
        let common_message = proto::CommonMessage{
            message_id: message_id.clone(),
            conversation_id: conversation_id.to_bytes(),
            sent_at: timestamp,
            payload: Some(proto::common_message::Payload::ChatMessage(
                        proto::ChatMessage {
                            content: chat_message.content,
                        }
                    ))
        };        
        let send_message = proto::Messaging {
            message: Some(proto::messaging::Message::CommonMessage(common_message.clone()))
        };
        
        
        log::error!("sender={}, receiver={}", user_account.id.to_base58(), receiver.to_base58());
        // send message via messaging
        match Messaging::pack_and_send_message(user_account, &receiver, &send_message.encode_to_vec(), Some(&message_id), true){
            Ok(signature)=>{
                // save 
                Self::save_outgoing_message(&user_account.id, &receiver, &conversation_id, &message_id, &common_message.encode_to_vec(), &signature, 1);
                Ok(signature)
            },
            Err(err)=>{
                Err(err)
            }
        }
    }


    // save an outgoing message to the data base
    fn save_outgoing_message(user_id: &PeerId, receiver_id: &PeerId, 
        conversation_id: &messaging::ConversationId, message_id: &Vec<u8>, 
        content: &Vec<u8>, signature: &Vec<u8>, status: u32) {
        // // create timestamp
        let timestamp = Timestamp::get_timestamp();        

        // // get data base of user account
        let db_ref = Self::get_user_db_ref(user_id.clone());

        // check if message_id is already exist
        if db_ref.message_ids.contains_key(message_id).unwrap(){
            return;
        }

        // check if group message
        let is_group = !(conversation_id.
            is_equal(&messaging::ConversationId::from_peers(user_id, receiver_id).unwrap()));        

        // get overview
        let overview;
        match Self::update_overview(user_id, receiver_id, &db_ref, &conversation_id.to_bytes(), 
            timestamp, content, &user_id.to_bytes(), is_group) {

            Ok(chat_overview) => overview = chat_overview,
            Err(e) => {
                log::error!("{}", e);
                return;
            }
        }

        // create data base key
        let key = Self::get_db_key_from_vec(&conversation_id.to_bytes(), overview.last_message_index);

        // // create chat message
        let message = rpc_proto::ChatMessage {
            index: overview.last_message_index,
            sender_id: user_id.to_bytes(),
            message_id: signature.clone(),
            status,
            is_group,
            conversation_id: conversation_id.to_bytes(),
            sent_at: timestamp,
            received_at: timestamp,
            content: content.clone(),
        };

        // save message in data base
        if let Err(e) = db_ref.messages.insert(key.clone(), message) {
            log::error!("Error saving chat message to data base: {}", e);
        }

        // flush trees to disk
        if let Err(e) = db_ref.messages.flush() {
            log::error!("Error chat messages flush: {}", e);
        }

        if let Err(e) = db_ref.message_ids.insert(message_id.clone(), key.clone()) {
            log::error!("Error saving chat messageid to data base: {}", e);
        }

        // flush trees to disk
        if let Err(e) = db_ref.message_ids.flush() {
            log::error!("Error chat message_ids flush: {}", e);
        }
    }
    

    // save an outgoing chat message to the data base
    fn save_outgoing_chat_message(user_id: PeerId, conversation_id: Vec<u8>, content: String, signature: Vec<u8>) {
        // let contents = rpc_proto::ChatMessageContent{
        //     content: Some(
        //         rpc_proto::chat_message_content::Content::ChatContent(
        //             rpc_proto::ChatContent{content}
        //         )
        //     )
        // };
        // Self::save_outgoing_message(user_id, conversation_id, contents.encode_to_vec(), signature, 0)
    }

    // save a sent file message to the data base
    pub fn save_outgoing_file_message(user_id: PeerId, conversation_id: Vec<u8>, file_name: String, file_size: u32, history_index: u64, file_id: u64, file_descr: String) {
        // let contents = rpc_proto::ChatMessageContent{
        //     content: Some(
        //         rpc_proto::chat_message_content::Content::FileContent(
        //             rpc_proto::FileShareContent{
        //                 history_index,
        //                 file_id,
        //                 file_name,
        //                 file_size,
        //                 file_descr,
        //             }
        //         )
        //     )
        // };
        // Self::save_outgoing_message(user_id, conversation_id, contents.encode_to_vec(), vec![], 1);
    }

    pub fn save_outgoing_group_invite_message(user_id: PeerId, conversation_id: PeerId, group_id: &Vec<u8>, group_name: String, created_at: u64, admin_id: &Vec<u8>, member_count: u32){
        // let contents = rpc_proto::ChatMessageContent{
        //     content: Some(
        //         rpc_proto::chat_message_content::Content::GroupInviteContent(
        //             rpc_proto::GroupInviteContent{
        //                 group_id: group_id.clone(),
        //                 group_name: group_name.clone(),
        //                 created_at,
        //                 member_count,
        //                 admin_id: admin_id.clone()
        //             }
        //         )
        //     )
        // };
        // Self::save_outgoing_message(user_id, conversation_id.to_bytes(), contents.encode_to_vec(), vec![], 1);
    }       
    pub fn save_outgoing_group_invite_reply_message(user_id: PeerId, conversation_id: PeerId, group_id: &Vec<u8>, accept: bool){
        // let contents = rpc_proto::ChatMessageContent{
        //     content: Some(
        //         rpc_proto::chat_message_content::Content::GroupInviteReplyContent(
        //             rpc_proto::GroupInviteReplyContent{
        //                 group_id: group_id.clone(),
        //                 accept,
        //             }
        //         )
        //     )
        // };
        // Self::save_outgoing_message(user_id, conversation_id.to_bytes(), contents.encode_to_vec(), vec![], 1);
    } 


    /// updating chat messge status as confirmed
    pub fn update_confirmation(user_id: &PeerId, message_id: &Vec<u8>, received_at: u64){
        // get data base of user account
        let db_ref = Self::get_user_db_ref(user_id.clone());
        if let Some(key) = db_ref.message_ids.get(message_id).unwrap() {
            if let Some(mut chat_msg) = db_ref.messages.get(&key).unwrap(){
                chat_msg.status = 2;
                chat_msg.received_at = received_at;

                // save message in data base
                if let Err(e) = db_ref.messages.insert(key.clone(), chat_msg) {
                    log::error!("Error saving chat message to data base: {}", e);
                }
                // flush trees to disk
                if let Err(e) = db_ref.messages.flush() {
                    log::error!("Error chat messages flush: {}", e);
                }
            }    
        }
    }
    
    /// Update the last Message and the Conversation Index of an Overview entry
    fn update_overview (user_id: &PeerId, peer_id: &PeerId,
        db_ref: &ChatUser, 
        conversation_id: &Vec<u8>, 
        timestamp: u64, 
        content: &Vec<u8>, 
        last_message_sender_id: &Vec<u8>, 
        b_group: bool) -> Result<rpc_proto::ChatOverview, String> {
        // check if there is an conversation
        let mut overview: rpc_proto::ChatOverview;

        match db_ref.overview.get(conversation_id.clone()) {
            // conversation exists
            Ok(Some(my_conversation)) => {
                overview = my_conversation;

                // update conversation
                overview.last_message_index = overview.last_message_index + 1;
                overview.last_message_at = timestamp;
                overview.unread = overview.unread +1;
                overview.content = content.clone();
                overview.last_message_sender_id = last_message_sender_id.clone();
            },
            // conversation does not exist yet            unconfirmed: chat_user.unconfirmed.clone(),    
            Ok(None) => {

                // get user name from known users
                let name;
                if b_group{
                    if let Some(group_name) = super::group::Group::get_group_name(user_id.clone(), &conversation_id){
                        name = group_name.clone();
                    }else{
                        return Err("Group not found".to_string());
                    }
                }else{
                    match router::users::Users::get_name(peer_id) {
                        Some(username) => name = username,
                        None => {
                            return Err("User not found".to_string());
                        }
                    }    
                }
                
                // create a new conversation
                overview = rpc_proto::ChatOverview {
                    conversation_id: conversation_id.clone(),
                    last_message_index: 1,
                    name,
                    last_message_at: timestamp,
                    unread: 1,
                    content: content.clone(),
                    last_message_sender_id: last_message_sender_id.clone(),
                };
            },
            // data base error
            Err(e) => {
                log::error!("{}", e);
                return Err("Error fetching conversation from data base".to_string());
            },
        }

        // save conversation overview in data base
        if let Err(e) = db_ref.overview.insert(conversation_id.clone(), overview.clone()) {
            log::error!("{}", e);
            return Err("Error saving chat overview to data base".to_string());
        }

        // flush tree to disk
        if let Err(e) = db_ref.overview.flush() {
            log::error!("Error chat overview flush: {}", e);
        }

        Ok(overview)
    }
    

    /// Get conversation overview list from data base
    fn get_overview(user_id: PeerId) -> rpc_proto::ChatOverviewList {
        // create empty conversation list
        let mut overview_list: Vec<rpc_proto::ChatOverview> = Vec::new();

        // get chat conversations overview tree for user
        let db_ref = Self::get_user_db_ref(user_id);

        // iterate over all values in db
        for res in db_ref.overview.iter() {
            if let Ok((_vec, conversation)) = res {
                overview_list.push(conversation);
            }
        }

        rpc_proto::ChatOverviewList {
            overview_list,
        }
    }

    /// Get chat messages of a specific conversation from data base
    fn get_messages(user_id: PeerId, conversation_id: Vec<u8>) -> rpc_proto::ChatConversationList {
        // create empty messages list
        let mut message_list: Vec<rpc_proto::ChatMessage> = Vec::new();

        // get database references for this user account
        let db_ref = Self::get_user_db_ref(user_id);

        let mut conversation_id0 =  conversation_id.clone();
        log::error!("id len={}", conversation_id.len());
        if conversation_id.len() > 16 {
            conversation_id0 = messaging::ConversationId::from_peers(&user_id, &PeerId::from_bytes(&conversation_id.clone()).unwrap()).unwrap().to_bytes();
        }
        
        log::error!("conversation id ={}", bs58::encode(conversation_id0.clone()).into_string());
        // create message keys
        let (first_key, last_key) = Self::get_db_key_range(&conversation_id0.clone());



        // iterate over all values in chat_messages db
        for res in db_ref.messages.range(first_key.as_slice()..last_key.as_slice()) {
            match res {
                Ok((_id, message)) => {
                    message_list.push(message);
                },
                Err(e) => {
                    log::error!("get_messages error: {}", e);
                }
            }
        }
        
        rpc_proto::ChatConversationList {
            conversation_id,
            message_list,
        }
    }

    /// get DB key range for a conversation ID
    ///
    /// returns a key tuple, which can be used to
    /// retrieve all messages for a user ID from the DB: 
    /// 
    /// (first_key, last_key)
    fn get_db_key_range(conversation_id: &Vec<u8>) -> (Vec<u8>, Vec<u8>) {
        let first_key = Self::get_db_key_from_vec(conversation_id, 0);
        let last_key = Self::get_db_key_from_vec(conversation_id, 0xFFFFFFFFFFFFFFFF); // = 4294967295
        (first_key, last_key)
    }

    // create DB key from conversation ID
    fn get_db_key_from_vec(conversation_id: &Vec<u8>, index: u64) -> Vec<u8> {
        let mut index_bytes = index.to_be_bytes().to_vec();
        let mut key_bytes = conversation_id.clone();
        key_bytes.append(&mut index_bytes);
        key_bytes
    }
    
    // get user data base tree references
    fn get_user_db_ref(user_id: PeerId) -> ChatUser {
        // check if user data exists
        {
            // get chat state
            let chat = CHAT.get().read().unwrap();

            // check if user ID is in map
            if let Some(chat_user) = chat.db_ref.get(&user_id.to_bytes()) {
                return ChatUser {
                    overview: chat_user.overview.clone(),
                    messages: chat_user.messages.clone(),
                    message_ids: chat_user.message_ids.clone(),
                };
            }
        }

        // create user data if it does not exist
        let chat_user = Self::create_chatuser(user_id);

        // return chat_user structure
        ChatUser {
            overview: chat_user.overview.clone(),
            messages: chat_user.messages.clone(),
            message_ids: chat_user.message_ids.clone(),
        }
    }

    // create user data when it does not exist
    fn create_chatuser(user_id: PeerId) -> ChatUser {
        // get user data base
        let db = DataBase::get_user_db(user_id);

        // open trees
        let overview: Tree<rpc_proto::ChatOverview> = db.open_bincode_tree("chat_overview").unwrap();
        let messages: Tree<rpc_proto::ChatMessage> = db.open_bincode_tree("chat_messages").unwrap();
        let message_ids: Tree<Vec<u8>> = db.open_bincode_tree("chat_message_ids").unwrap();

        let chat_user = ChatUser {
            overview,
            messages,
            message_ids,
        };

        // get chat state for writing
        let mut chat = CHAT.get().write().unwrap();

        // add user to state
        chat.db_ref.insert( user_id.to_bytes(), chat_user.clone());

        // return structure
        chat_user
    }

    /// Process incoming RPC request messages for chat module
    pub fn rpc(data: Vec<u8>, user_id: Vec<u8>, _lan: Option<&mut Lan>, _internet: Option<&mut Internet> ) {
        let my_user_id = PeerId::from_bytes(&user_id).unwrap();

        match rpc_proto::Chat::decode(&data[..]) {
            Ok(chat) => {
                match chat.message {
                    Some(rpc_proto::chat::Message::OverviewRequest(_overview_request)) => {
                        // get overview list from data base
                        let overview_list = Self::get_overview(my_user_id);

                        // pack message
                        let proto_message = rpc_proto::Chat {
                            message: Some( 
                                rpc_proto::chat::Message::OverviewList(overview_list))};
                        // encode message
                        let mut buf = Vec::with_capacity(proto_message.encoded_len());
                        proto_message.encode(&mut buf).expect("Vec<u8> provides capacity as needed");

                        // send message
                        Rpc::send_message(buf, crate::rpc::proto::Modules::Chat.into(), "".to_string(), Vec::new() );
                    },
                    Some(rpc_proto::chat::Message::ConversationRequest(conversation_request)) => {
                        // get messages of a conversation from data base
                        let conversation_list = Self::get_messages(my_user_id, conversation_request.conversation_id);

                        // pack message
                        let proto_message = rpc_proto::Chat {
                            message: Some( 
                                rpc_proto::chat::Message::ConversationList(conversation_list)
                            ),
                        };

                        // encode message
                        let mut buf = Vec::with_capacity(proto_message.encoded_len());
                        proto_message.encode(&mut buf).expect("Vec<u8> provides capacity as needed");
                        Rpc::send_message(buf, crate::rpc::proto::Modules::Chat.into(), "".to_string(), Vec::new() );
                        // send messageproto::Container, "".to_string(), Vec::new() );
                    },
                    Some(rpc_proto::chat::Message::ChatGroupRequest(conversation_request)) => {
                        // get messages of a conversation from data base
                        let conversation_list = Self::get_messages(my_user_id, conversation_request.group_id);

                        let chat_group_list = rpc_proto::ChatGroupList{
                            group_id: conversation_list.conversation_id.clone(),
                            message_list: conversation_list.message_list
                        };

                        // pack message
                        let proto_message = rpc_proto::Chat {
                            message: Some( 
                                rpc_proto::chat::Message::ChatGroupList(chat_group_list)
                            ),
                        };

                        // encode message
                        let mut buf = Vec::with_capacity(proto_message.encoded_len());
                        proto_message.encode(&mut buf).expect("Vec<u8> provides capacity as needed");

                        // send message
                        Rpc::send_message(buf, crate::rpc::proto::Modules::Chat.into(), "".to_string(), Vec::new() );
                    },

                    Some(rpc_proto::chat::Message::Send(message)) => {
                        // print message
                        log::info!("sending chat message: {}", message.content.clone());

                        // get user account from user_id
                        let user_account;
                        match PeerId::from_bytes(&user_id){
                            Ok(user_id_decoded) => {
                                match UserAccounts::get_by_id(user_id_decoded) {
                                    Some(account) => {
                                        user_account = account;
                                    },
                                    None => {
                                        log::error!("user account id not found: {:?}", user_id_decoded.to_base58());
                                        return
                                    },
                                }    
                            },
                            Err(e) => {
                                log::error!("user account id could'nt be encoded: {:?}", e);
                                return
                            },
                        }

                        // send the message
                        match Self::send( &user_account, message.clone() ) {
                            Ok(signature) => {
                                // save the message to data base
                                Self::save_outgoing_chat_message(user_account.id, message.conversation_id, message.content, signature);
                            },
                            Err(e) => {
                                log::error!("Outgoing chat message error: {}", e)
                            }
                        }
                    },
                    _ => {
                        log::error!("Unhandled Protobuf Chat Message");
                    },
                }    
            },
            Err(error) => {
                log::error!("{:?}", error);
            },
        }
    }
}
