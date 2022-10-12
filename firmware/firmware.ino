/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#include <iostream>
#include <vector>
#include "ws2812b.h"
#include "image.h"
#include "hall.h"
#include "bt.h"

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************

const int PIN_NUMBER_OF_LED_STRIP_1 = 15;
const int NUMBER_OF_LEDS_IN_LED_STRIP_1 = 63;
const int PIN_NUMBER_OF_HALL_SENSOR = 4;
const int IMAGE_SIZE_IN_BYTES = (NUMBER_OF_LEDS_IN_LED_STRIP_1 * NUMBER_OF_LEDS_IN_LED_STRIP_1 * 3);

#define PRINT_TIME_OF_LED_UPDATE 0

/// ********************************************************************************************************************
/// global objects
/// ********************************************************************************************************************

// WS2812B led_strip_1(PIN_NUMBER_OF_LED_STRIP_1, NUMBER_OF_LEDS_IN_LED_STRIP_1);
// Hall hall_sensor(PIN_NUMBER_OF_HALL_SENSOR);
// Image<WS2812B> current_image(led_strip_1, NUMBER_OF_LEDS_IN_LED_STRIP_1);

/// ********************************************************************************************************************
/// SETUP
/// ********************************************************************************************************************

void setup() {
  Serial.begin(115200);
  bluetooth_begin();
  // current_image.update_image_for_testing();
}

/// ********************************************************************************************************************
/// LOOP
/// ********************************************************************************************************************

void loop() {
  int loop_number = 0;
  while (true) {
    loop_number++;
    unsigned long checkpoint_0 = micros();
    // int theta = hall_sensor.get_angle();
    unsigned long checkpoint_1 = micros();
    // vector<uint32_t>& v = current_image.get_led_strip_colors(theta);
    unsigned long checkpoint_2 = micros();
    // led_strip_1.update_LED_fast(v);
    unsigned long checkpoint_3 = micros();

    // check if new image is being received.
    if (bluetooth_available()) {
      Serial.println("Some more bytes are available.");
      int i = 0;
      while (bluetooth_available()) {
        auto image_bytes = bluetooth_read();
        // current_image.update_image_byte_by_byte((uint8_t)image_bytes);
        i++;
      }
      Serial.print("Number of bytes read = ");
      Serial.println(i);
    }

#if PRINT_TIME_OF_LED_UPDATE
    if (loop_number % 10000 == 0) {
      bluetooth_print("Theta calculation time = ");
      bluetooth_print(String(checkpoint_1 - checkpoint_0));
      bluetooth_print(", LED vector finding time = ");
      bluetooth_print(String(checkpoint_2 - checkpoint_1));
      bluetooth_print(", updating LED time = ");
      bluetooth_print(String(checkpoint_3 - checkpoint_2));
      bluetooth_print(", total image Update time = ");
      bluetooth_print(String(checkpoint_3 - checkpoint_0));
      bluetooth_print("\n");
      hall_sensor.printHallStats();
    }
#endif
  }
}