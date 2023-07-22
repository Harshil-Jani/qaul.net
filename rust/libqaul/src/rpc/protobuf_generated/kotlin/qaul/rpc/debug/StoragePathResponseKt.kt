// Generated by the protocol buffer compiler. DO NOT EDIT!
// source: rpc/debug.proto

// Generated files should ignore deprecation warnings
@file:Suppress("DEPRECATION")
package qaul.rpc.debug;

@kotlin.jvm.JvmName("-initializestoragePathResponse")
public inline fun storagePathResponse(block: qaul.rpc.debug.StoragePathResponseKt.Dsl.() -> kotlin.Unit): qaul.rpc.debug.DebugOuterClass.StoragePathResponse =
  qaul.rpc.debug.StoragePathResponseKt.Dsl._create(qaul.rpc.debug.DebugOuterClass.StoragePathResponse.newBuilder()).apply { block() }._build()
/**
 * ```
 * StoragePathResponse
 *
 * Contains Storage Path
 * ```
 *
 * Protobuf type `qaul.rpc.debug.StoragePathResponse`
 */
public object StoragePathResponseKt {
  @kotlin.OptIn(com.google.protobuf.kotlin.OnlyForUseByGeneratedProtoCode::class)
  @com.google.protobuf.kotlin.ProtoDslMarker
  public class Dsl private constructor(
    private val _builder: qaul.rpc.debug.DebugOuterClass.StoragePathResponse.Builder
  ) {
    public companion object {
      @kotlin.jvm.JvmSynthetic
      @kotlin.PublishedApi
      internal fun _create(builder: qaul.rpc.debug.DebugOuterClass.StoragePathResponse.Builder): Dsl = Dsl(builder)
    }

    @kotlin.jvm.JvmSynthetic
    @kotlin.PublishedApi
    internal fun _build(): qaul.rpc.debug.DebugOuterClass.StoragePathResponse = _builder.build()

    /**
     * `string storage_path = 1;`
     */
    public var storagePath: kotlin.String
      @JvmName("getStoragePath")
      get() = _builder.getStoragePath()
      @JvmName("setStoragePath")
      set(value) {
        _builder.setStoragePath(value)
      }
    /**
     * `string storage_path = 1;`
     */
    public fun clearStoragePath() {
      _builder.clearStoragePath()
    }
  }
}
@kotlin.jvm.JvmSynthetic
public inline fun qaul.rpc.debug.DebugOuterClass.StoragePathResponse.copy(block: qaul.rpc.debug.StoragePathResponseKt.Dsl.() -> kotlin.Unit): qaul.rpc.debug.DebugOuterClass.StoragePathResponse =
  qaul.rpc.debug.StoragePathResponseKt.Dsl._create(this.toBuilder()).apply { block() }._build()

