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
/// namespace definition
/// ********************************************************************************************************************

namespace bluetooth {

/// ********************************************************************************************************************
/// protected variable
/// ********************************************************************************************************************

namespace {
BluetoothSerial _SerialBT;
}

/// ********************************************************************************************************************
/// functions
/// ********************************************************************************************************************

void begin() {
  bool success = _SerialBT.begin("ESP32test");
  if (!success) {
    Serial.println("An error occurred initializing Bluetooth.");
    ESP.restart();
  } else {
    Serial.println("Bluetooth initialized.");
  }
}

int available(void) {
  return _SerialBT.available();
}

int read(void) {
  return _SerialBT.read();
}

void print(const String& string1) {
  Serial.print(string1);
}

}