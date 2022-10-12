/// ********************************************************************************************************************
/// multiple include protection
/// ********************************************************************************************************************

#pragma once

/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************

/// ********************************************************************************************************************
/// Foward declarations
/// ********************************************************************************************************************


/// ********************************************************************************************************************
/// global bt
/// ********************************************************************************************************************

BluetoothSerial SerialBT;

/// ********************************************************************************************************************
/// functions
/// ********************************************************************************************************************

void bluetooth_begin() {
  bool success = SerialBT.begin("ESP32test");
  if (!success) {
    Serial.println("An error occurred initializing Bluetooth");
    ESP.restart();
  } else {
    Serial.println("Bluetooth Initialized");
  }
}

int bluetooth_available(void) {
  return SerialBT.available();
}

int bluetooth_read(void) {
  return SerialBT.read();
}

void bluetooth_print(const String& string1) {
  Serial.print(string1);
}