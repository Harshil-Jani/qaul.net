// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: qaul_rpc.proto

package qaul_rpc.pb;

public final class QaulRpc {
  private QaulRpc() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\016qaul_rpc.proto\022\013qaul_rpc.pb\032\022from_libq" +
      "aul.proto\032\020to_libqaul.protoP\000P\001b\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
          qaul_rpc.pb.FromLibqaulOuterClass.getDescriptor(),
          qaul_rpc.pb.ToLibqaulOuterClass.getDescriptor(),
        });
    qaul_rpc.pb.FromLibqaulOuterClass.getDescriptor();
    qaul_rpc.pb.ToLibqaulOuterClass.getDescriptor();
  }

  // @@protoc_insertion_point(outer_class_scope)
}
