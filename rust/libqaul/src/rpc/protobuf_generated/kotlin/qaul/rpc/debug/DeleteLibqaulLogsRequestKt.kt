// Generated by the protocol buffer compiler. DO NOT EDIT!
// source: rpc/debug.proto

// Generated files should ignore deprecation warnings
@file:Suppress("DEPRECATION")
package qaul.rpc.debug;

@kotlin.jvm.JvmName("-initializedeleteLibqaulLogsRequest")
public inline fun deleteLibqaulLogsRequest(block: qaul.rpc.debug.DeleteLibqaulLogsRequestKt.Dsl.() -> kotlin.Unit): qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest =
  qaul.rpc.debug.DeleteLibqaulLogsRequestKt.Dsl._create(qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest.newBuilder()).apply { block() }._build()
/**
 * ```
 * DeleteLibqaulLogsRequest
 *
 * Requests for the log folder to be wiped clean
 * ```
 *
 * Protobuf type `qaul.rpc.debug.DeleteLibqaulLogsRequest`
 */
public object DeleteLibqaulLogsRequestKt {
  @kotlin.OptIn(com.google.protobuf.kotlin.OnlyForUseByGeneratedProtoCode::class)
  @com.google.protobuf.kotlin.ProtoDslMarker
  public class Dsl private constructor(
    private val _builder: qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest.Builder
  ) {
    public companion object {
      @kotlin.jvm.JvmSynthetic
      @kotlin.PublishedApi
      internal fun _create(builder: qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest.Builder): Dsl = Dsl(builder)
    }

    @kotlin.jvm.JvmSynthetic
    @kotlin.PublishedApi
    internal fun _build(): qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest = _builder.build()
  }
}
@kotlin.jvm.JvmSynthetic
public inline fun qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest.copy(block: qaul.rpc.debug.DeleteLibqaulLogsRequestKt.Dsl.() -> kotlin.Unit): qaul.rpc.debug.DebugOuterClass.DeleteLibqaulLogsRequest =
  qaul.rpc.debug.DeleteLibqaulLogsRequestKt.Dsl._create(this.toBuilder()).apply { block() }._build()

