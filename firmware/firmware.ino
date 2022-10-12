/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#include "ws2812b.h"
#include "image.h"
#include "hall.h"
#include "bluetooth.h"

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************

#define PRINT_TIME_OF_LED_UPDATE 0

/// ********************************************************************************************************************
/// SETUP
/// ********************************************************************************************************************

void setup() {
  Serial.begin(115200);
  bluetooth::begin();
  ws2812b::begin();
  image::begin();
  hall::begin();
  image::update_image_for_testing();
}

/// ********************************************************************************************************************
/// LOOP
/// ********************************************************************************************************************

void loop() {
  // this if is to speed up handling when BT data is pending.
  if (!bluetooth::available()) {
    unsigned long checkpoint_0 = micros();
    int theta = hall::get_angle();
    unsigned long checkpoint_1 = micros();
    auto v = image::get_led_strip_colors(theta);
    unsigned long checkpoint_2 = micros();
    ws2812b::update_LED(v);
    unsigned long checkpoint_3 = micros();
  }

  // check if new image is being received.
  if (bluetooth::available()) {
    Serial.println("Some more bytes are available.");
    int i = 0;
    while (bluetooth::available()) {
      auto image_bytes = bluetooth::read();
      image::update_image_byte_by_byte((uint8_t)image_bytes);
      i++;
    }
    Serial.print("Number of bytes read = ");
    Serial.println(i);
  }
}