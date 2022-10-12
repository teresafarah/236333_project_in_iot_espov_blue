/// ********************************************************************************************************************
/// multiple include protection
/// ********************************************************************************************************************

#pragma once

/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#define BLUETOOTH_ON  1

#if BLUETOOTH_ON

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

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

#if BLUETOOTH_ON
BluetoothSerial SerialBT;
#endif

void print_to_bt(const String& string1){
#if BLUETOOTH_ON
  for (int i = 0; i < string1.length(); ++i){
    SerialBT.write(string1.charAt(i));
  }
#else
  Serial.print(string1);
#endif
}

void begin_serial_bt_connection() {
#if BLUETOOTH_ON
  SerialBT.begin("MATESP32Bluetooth");
  Serial.println("Bluetooth Started! Ready to pair...");
#endif
}

bool is_bt_data_available() {
  return SerialBT.available() ;
}

void read_bt_data_to_vector(vector<uint8_t>& bytes) {
  while (SerialBT.available()) {
    uint8_t b = SerialBT.read();
    bytes.push_back(b);
  }
}
