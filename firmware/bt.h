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

vector<byte> read_bt_data() {
  const int NUMBER_OF_BYTES = 63 * 63 * 3;
//  Serial.println("Allocate bytes.");
//  Serial.flush();
  vector<byte> bytes(NUMBER_OF_BYTES);
  Serial.println("Reading start.");
  Serial.flush();
  for (int i = 0; i < NUMBER_OF_BYTES ; ++ i){
//    Serial.println("Reading byte.");
//    Serial.flush();
    while(SerialBT.available() == false) {}
    byte b = SerialBT.read();
    bytes.push_back(b);
  }
  Serial.println("Reading end.");
  Serial.flush();

  Serial.println("bytes length = " + String(bytes.size()));
  
  return bytes;
//  while (SerialBT.available()) {
//    uint8_t b = SerialBT.read();
//    bytes.push_back(b);
//  }
}
