import 'dart:math';
import 'dart:typed_data';

import 'package:fast_base58/fast_base58.dart';

class BleConnectionStatus {
  final Uint8List bleId;
  final String? status;
  final Uint8List? deviceInfo;
  final int discoveredNodes;
  final int nodesPendingConfirmation;

  BleConnectionStatus({
    required this.bleId,
    this.status,
    this.deviceInfo,
    this.discoveredNodes = 0,
    this.nodesPendingConfirmation = 0,
  });

  String get idBase58 => Base58Encode(bleId);

  String? get deviceInfoBase58 =>
      deviceInfo == null ? null : Base58Encode(deviceInfo!);

  BleConnectionStatus copyWith({
    String? status,
    Uint8List? deviceInfo,
    int discoveredNodes = 0,
    int nodesPendingConfirmation = 0,
  }) {
    return BleConnectionStatus(
      bleId: bleId,
      status: status ?? this.status,
      deviceInfo: deviceInfo ?? this.deviceInfo,
      discoveredNodes: max(discoveredNodes, this.discoveredNodes),
      nodesPendingConfirmation:
          max(nodesPendingConfirmation, this.nodesPendingConfirmation),
    );
  }

  @override
  String toString() => '''
BleConnectionStatus{
  bleId: $bleId,
  status: $status,
  deviceInfo: $deviceInfo,
  discoveredNodes: $discoveredNodes,
  nodesPendingConfirmation: $nodesPendingConfirmation
}
''';
}