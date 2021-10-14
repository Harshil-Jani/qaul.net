// Copyright (c) 2021 Open Community Project Association https://ocpa.ch
// This software is published under the AGPLv3 license.

//! # C-API for the threaded libqaul
//! 
//! This is the C compatible FFI of libqaul.
//! It can be used to start libqaul in an own
//! thread and communicate thread safe with it.
//! All functions are thread safe and can be
//! called from any external thread.

use std::ffi::CString;
use std::os::raw::c_char;

/// test function
#[no_mangle]
pub extern "C" fn hello() -> *mut c_char {
    CString::new("Hello qaul!")
        .unwrap()
        .into_raw()
}

/// start libqaul in an own thread
/// 
/// This function initializes and starts libqaul.
/// It needs to be called before any other function
/// of this API.
#[no_mangle]
pub extern "C" fn start() {
    #[cfg(target_os = "android")]
    super::start_android();

    #[cfg(not(target_os = "android"))]
    super::start();
}

/// check if libqaul finished initializing
/// 
/// Returns 1 when it finished, otherwise 0.
/// 
/// 1: initialization finished
/// 0: libqaul not initialized
/// 
/// Don't send any messages to libqaul before it finished initializing.
#[no_mangle]
pub extern "C" fn initialized() -> i32 {
    if super::initialization_finished() {
        return 1
    }

    0
}

/// send RPC messages to libqaul
/// 
/// returns 0 on success and negative numbers on failure
/// 
/// 0  : success
/// -1 : pointer is null
/// -2 : message is too big
#[no_mangle]
pub extern "C" fn send_rpc_to_libqaul(message: *const u8, message_length: u32) -> i32 {
    // message-pointer sanity check
    if message.is_null() {
        log::error!("message pointer is null");
        return -1
    }

    // check for message length
    // set a maximum message size to 500'000 bytes
    if message_length > 500000 {
        log::error!("message size to big! size is {} bytes", message_length);
        return -2
    }

    // copy input buffer to libqaul
    log::info!("copy {} bytes of message buffer", message_length);
    let message_length_usize: usize = message_length as usize;
    let mut rust_buffer_owned: Vec<u8>;
    unsafe {
        //std::ptr::copy_nonoverlapping(message, rust_buffer.as_mut_ptr(), message_length_usize);
        let rust_buffer = &std::slice::from_raw_parts(message, message_length_usize).to_vec();
        rust_buffer_owned = rust_buffer.iter().cloned().collect();
    }
    log::info!("received message: {:02x?}", rust_buffer_owned);

    // send it further to libqaul
    crate::rpc::Rpc::send_to_libqaul(rust_buffer_owned);

    // return success
    0
}


/// receive RPC messages from libqaul
/// 
/// You need to provide the pointer to a buffer and declare
/// the length of a buffer.
/// If a message was received, this function copies the message
/// into the buffer.
/// 
/// The function returns the length of the message.
/// The return value '0' means no message was received. 
/// 
/// A negative value is an error.
/// -1 : an error occurred
/// -2 : buffer to small
/// -3 : buffer pointer is null
#[no_mangle]
pub extern "C" fn receive_rpc_from_libqaul(buffer: *mut libc::c_uchar, buffer_length: u32) -> i32 {
    // poll rpc channel
    let received = crate::rpc::Rpc::receive_from_libqaul();

    match received {
        Ok(message) => {
            // check if no message
            if message.len() == 0 {
                return 0
            }

            // buffer-pointer sanity check
            if buffer.is_null() {
                log::error!("provided buffer pointer is null");
                return -3
            }

            // check buffer len
            let buffer_length_usize: usize = buffer_length as usize;
            if message.len() >= buffer_length_usize {
                log::error!("Buffer size to small! message size: {} < buffer size {}", message.len(), buffer_length);
                // return -2: buffer size to small
                return -2            
            }

            // copy message into provided buffer
            unsafe {
                std::ptr::copy_nonoverlapping(message.as_ptr(), buffer, message.len());
            }
                
            // // https://doc.rust-lang.org/std/mem/fn.transmute.html
            // let u8_slice = unsafe {
            // &*( &slice as *const [c_char] as *const [u8])
            // };

            // unsafe {
            //     //buffer.copy_from_nonoverlapping(message, message.len());
            //     //let msg = message;
            //     //std::ptr::copy_nonoverlapping(message, buffer, message.len());
            // }

            // return message length
            let len: i32 = message.len() as i32;
            return len
        },
        Err(err) => {
            // log error message
            log::error!("{:?}", err);
            // return -1: an error occurred
            return -1
        },
    }

    /// Get the number of messages cued for receiving
    #[no_mangle]
    pub extern "C" fn receive_rpc_from_libqaul_queued_length() -> i32 {
        // check rpc queue len
        crate::rpc::Rpc::receive_from_libqaul_queue_length() as i32
    }

    /// Get the number of messages ever sent to rpc.
    /// The counter is increased with every message sent to libqaul.
    /// This function is mainly for debugging.
    #[no_mangle]
    pub extern "C" fn send_rpc_to_libqaul_count() -> i32 {
        // get message count of messages sent to libqaul
        crate::rpc::Rpc::send_rpc_count()
    }
}