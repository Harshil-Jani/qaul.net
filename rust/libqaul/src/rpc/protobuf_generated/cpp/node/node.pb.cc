// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: node/node.proto

#include "node/node.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace qaul {
namespace rpc {
namespace node {
constexpr Node::Node(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : _oneof_case_{}{}
struct NodeDefaultTypeInternal {
  constexpr NodeDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~NodeDefaultTypeInternal() {}
  union {
    Node _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT NodeDefaultTypeInternal _Node_default_instance_;
constexpr NodeInformation::NodeInformation(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : id_base58_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct NodeInformationDefaultTypeInternal {
  constexpr NodeInformationDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~NodeInformationDefaultTypeInternal() {}
  union {
    NodeInformation _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT NodeInformationDefaultTypeInternal _NodeInformation_default_instance_;
}  // namespace node
}  // namespace rpc
}  // namespace qaul
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_node_2fnode_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_node_2fnode_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_node_2fnode_2eproto = nullptr;

const uint32_t TableStruct_node_2fnode_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::qaul::rpc::node::Node, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::qaul::rpc::node::Node, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::qaul::rpc::node::Node, message_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::qaul::rpc::node::NodeInformation, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::qaul::rpc::node::NodeInformation, id_base58_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::qaul::rpc::node::Node)},
  { 9, -1, -1, sizeof(::qaul::rpc::node::NodeInformation)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::qaul::rpc::node::_Node_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::qaul::rpc::node::_NodeInformation_default_instance_),
};

const char descriptor_table_protodef_node_2fnode_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017node/node.proto\022\rqaul.rpc.node\"Z\n\004Node"
  "\022\027\n\rget_node_info\030\001 \001(\010H\000\022.\n\004info\030\002 \001(\0132"
  "\036.qaul.rpc.node.NodeInformationH\000B\t\n\007mes"
  "sage\"$\n\017NodeInformation\022\021\n\tid_base58\030\001 \001"
  "(\tb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_node_2fnode_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_node_2fnode_2eproto = {
  false, false, 170, descriptor_table_protodef_node_2fnode_2eproto, "node/node.proto", 
  &descriptor_table_node_2fnode_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_node_2fnode_2eproto::offsets,
  file_level_metadata_node_2fnode_2eproto, file_level_enum_descriptors_node_2fnode_2eproto, file_level_service_descriptors_node_2fnode_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_node_2fnode_2eproto_getter() {
  return &descriptor_table_node_2fnode_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_node_2fnode_2eproto(&descriptor_table_node_2fnode_2eproto);
namespace qaul {
namespace rpc {
namespace node {

// ===================================================================

class Node::_Internal {
 public:
  static const ::qaul::rpc::node::NodeInformation& info(const Node* msg);
};

const ::qaul::rpc::node::NodeInformation&
Node::_Internal::info(const Node* msg) {
  return *msg->message_.info_;
}
void Node::set_allocated_info(::qaul::rpc::node::NodeInformation* info) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  clear_message();
  if (info) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::qaul::rpc::node::NodeInformation>::GetOwningArena(info);
    if (message_arena != submessage_arena) {
      info = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, info, submessage_arena);
    }
    set_has_info();
    message_.info_ = info;
  }
  // @@protoc_insertion_point(field_set_allocated:qaul.rpc.node.Node.info)
}
Node::Node(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:qaul.rpc.node.Node)
}
Node::Node(const Node& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  clear_has_message();
  switch (from.message_case()) {
    case kGetNodeInfo: {
      _internal_set_get_node_info(from._internal_get_node_info());
      break;
    }
    case kInfo: {
      _internal_mutable_info()->::qaul::rpc::node::NodeInformation::MergeFrom(from._internal_info());
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:qaul.rpc.node.Node)
}

inline void Node::SharedCtor() {
clear_has_message();
}

Node::~Node() {
  // @@protoc_insertion_point(destructor:qaul.rpc.node.Node)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Node::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (has_message()) {
    clear_message();
  }
}

void Node::ArenaDtor(void* object) {
  Node* _this = reinterpret_cast< Node* >(object);
  (void)_this;
}
void Node::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Node::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Node::clear_message() {
// @@protoc_insertion_point(one_of_clear_start:qaul.rpc.node.Node)
  switch (message_case()) {
    case kGetNodeInfo: {
      // No need to clear
      break;
    }
    case kInfo: {
      if (GetArenaForAllocation() == nullptr) {
        delete message_.info_;
      }
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = MESSAGE_NOT_SET;
}


void Node::Clear() {
// @@protoc_insertion_point(message_clear_start:qaul.rpc.node.Node)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_message();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Node::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool get_node_info = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _internal_set_get_node_info(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .qaul.rpc.node.NodeInformation info = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_info(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Node::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:qaul.rpc.node.Node)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bool get_node_info = 1;
  if (_internal_has_get_node_info()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(1, this->_internal_get_node_info(), target);
  }

  // .qaul.rpc.node.NodeInformation info = 2;
  if (_internal_has_info()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::info(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:qaul.rpc.node.Node)
  return target;
}

size_t Node::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:qaul.rpc.node.Node)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  switch (message_case()) {
    // bool get_node_info = 1;
    case kGetNodeInfo: {
      total_size += 1 + 1;
      break;
    }
    // .qaul.rpc.node.NodeInformation info = 2;
    case kInfo: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *message_.info_);
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Node::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Node::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Node::GetClassData() const { return &_class_data_; }

void Node::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Node *>(to)->MergeFrom(
      static_cast<const Node &>(from));
}


void Node::MergeFrom(const Node& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:qaul.rpc.node.Node)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.message_case()) {
    case kGetNodeInfo: {
      _internal_set_get_node_info(from._internal_get_node_info());
      break;
    }
    case kInfo: {
      _internal_mutable_info()->::qaul::rpc::node::NodeInformation::MergeFrom(from._internal_info());
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Node::CopyFrom(const Node& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:qaul.rpc.node.Node)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Node::IsInitialized() const {
  return true;
}

void Node::InternalSwap(Node* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(message_, other->message_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata Node::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_node_2fnode_2eproto_getter, &descriptor_table_node_2fnode_2eproto_once,
      file_level_metadata_node_2fnode_2eproto[0]);
}

// ===================================================================

class NodeInformation::_Internal {
 public:
};

NodeInformation::NodeInformation(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:qaul.rpc.node.NodeInformation)
}
NodeInformation::NodeInformation(const NodeInformation& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  id_base58_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    id_base58_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_id_base58().empty()) {
    id_base58_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_id_base58(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:qaul.rpc.node.NodeInformation)
}

inline void NodeInformation::SharedCtor() {
id_base58_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  id_base58_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

NodeInformation::~NodeInformation() {
  // @@protoc_insertion_point(destructor:qaul.rpc.node.NodeInformation)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void NodeInformation::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  id_base58_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void NodeInformation::ArenaDtor(void* object) {
  NodeInformation* _this = reinterpret_cast< NodeInformation* >(object);
  (void)_this;
}
void NodeInformation::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void NodeInformation::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void NodeInformation::Clear() {
// @@protoc_insertion_point(message_clear_start:qaul.rpc.node.NodeInformation)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_base58_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* NodeInformation::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string id_base58 = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_id_base58();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "qaul.rpc.node.NodeInformation.id_base58"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* NodeInformation::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:qaul.rpc.node.NodeInformation)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string id_base58 = 1;
  if (!this->_internal_id_base58().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_id_base58().data(), static_cast<int>(this->_internal_id_base58().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "qaul.rpc.node.NodeInformation.id_base58");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_id_base58(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:qaul.rpc.node.NodeInformation)
  return target;
}

size_t NodeInformation::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:qaul.rpc.node.NodeInformation)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string id_base58 = 1;
  if (!this->_internal_id_base58().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_id_base58());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData NodeInformation::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    NodeInformation::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*NodeInformation::GetClassData() const { return &_class_data_; }

void NodeInformation::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<NodeInformation *>(to)->MergeFrom(
      static_cast<const NodeInformation &>(from));
}


void NodeInformation::MergeFrom(const NodeInformation& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:qaul.rpc.node.NodeInformation)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_id_base58().empty()) {
    _internal_set_id_base58(from._internal_id_base58());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void NodeInformation::CopyFrom(const NodeInformation& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:qaul.rpc.node.NodeInformation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NodeInformation::IsInitialized() const {
  return true;
}

void NodeInformation::InternalSwap(NodeInformation* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &id_base58_, lhs_arena,
      &other->id_base58_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata NodeInformation::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_node_2fnode_2eproto_getter, &descriptor_table_node_2fnode_2eproto_once,
      file_level_metadata_node_2fnode_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace node
}  // namespace rpc
}  // namespace qaul
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::qaul::rpc::node::Node* Arena::CreateMaybeMessage< ::qaul::rpc::node::Node >(Arena* arena) {
  return Arena::CreateMessageInternal< ::qaul::rpc::node::Node >(arena);
}
template<> PROTOBUF_NOINLINE ::qaul::rpc::node::NodeInformation* Arena::CreateMaybeMessage< ::qaul::rpc::node::NodeInformation >(Arena* arena) {
  return Arena::CreateMessageInternal< ::qaul::rpc::node::NodeInformation >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
