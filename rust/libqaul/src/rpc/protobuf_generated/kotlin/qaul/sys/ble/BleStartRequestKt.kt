//Generated by the protocol buffer compiler. DO NOT EDIT!
// source: connections/ble/manager/ble.proto

package qaul.sys.ble;

@kotlin.jvm.JvmSynthetic
inline fun bleStartRequest(block: qaul.sys.ble.BleStartRequestKt.Dsl.() -> Unit): qaul.sys.ble.BleOuterClass.BleStartRequest =
  qaul.sys.ble.BleStartRequestKt.Dsl._create(qaul.sys.ble.BleOuterClass.BleStartRequest.newBuilder()).apply { block() }._build()
object BleStartRequestKt {
  @kotlin.OptIn(com.google.protobuf.kotlin.OnlyForUseByGeneratedProtoCode::class)
  @com.google.protobuf.kotlin.ProtoDslMarker
  class Dsl private constructor(
    @kotlin.jvm.JvmField private val _builder: qaul.sys.ble.BleOuterClass.BleStartRequest.Builder
  ) {
    companion object {
      @kotlin.jvm.JvmSynthetic
      @kotlin.PublishedApi
      internal fun _create(builder: qaul.sys.ble.BleOuterClass.BleStartRequest.Builder): Dsl = Dsl(builder)
    }

    @kotlin.jvm.JvmSynthetic
    @kotlin.PublishedApi
    internal fun _build(): qaul.sys.ble.BleOuterClass.BleStartRequest = _builder.build()
  }
}
@kotlin.jvm.JvmSynthetic
inline fun qaul.sys.ble.BleOuterClass.BleStartRequest.copy(block: qaul.sys.ble.BleStartRequestKt.Dsl.() -> Unit): qaul.sys.ble.BleOuterClass.BleStartRequest =
  qaul.sys.ble.BleStartRequestKt.Dsl._create(this.toBuilder()).apply { block() }._build()