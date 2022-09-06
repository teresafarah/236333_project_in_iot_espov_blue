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

const int PIN_NUMBER_OF_LED_STRIP_1 =           15;
const int NUMBER_OF_LEDS_IN_LED_STRIP_1 =       63;
const int PIN_NUMBER_OF_HALL_SENSOR =           4;

#define PRINT_TIME_OF_LED_UPDATE                               1

/// ********************************************************************************************************************
/// global objects
/// ********************************************************************************************************************

WS2812B led_strip_1(PIN_NUMBER_OF_LED_STRIP_1, NUMBER_OF_LEDS_IN_LED_STRIP_1);
Hall hall_sensor(PIN_NUMBER_OF_HALL_SENSOR);
Image<WS2812B> current_image(led_strip_1, NUMBER_OF_LEDS_IN_LED_STRIP_1);

/// ********************************************************************************************************************
/// SETUP
/// ********************************************************************************************************************

void setup() {
	Serial.begin(115200);
  current_image.update_image_for_testing();
  begin_serial_bt_connection();
}

/// ********************************************************************************************************************
/// LOOP
/// ********************************************************************************************************************

void loop() {
  int loop_number = 0;
  while(true) {
    loop_number ++;
    unsigned long checkpoint_0 = micros();
    int theta = hall_sensor.get_angle();
    unsigned long checkpoint_1 = micros();
    vector<uint32_t>& v = current_image.get_led_strip_colors(theta);
    unsigned long checkpoint_2 = micros();
    led_strip_1.update_LED_fast(v);
    unsigned long checkpoint_3 = micros();
#if PRINT_TIME_OF_LED_UPDATE
    if (loop_number % 10000 == 0){
      print_to_bt("Theta calculation time = ");
      print_to_bt(String(checkpoint_1 - checkpoint_0));
      print_to_bt(", LED vector finding time = ");
      print_to_bt(String(checkpoint_2 - checkpoint_1));
      print_to_bt(", updating LED time = ");
      print_to_bt(String(checkpoint_3 - checkpoint_2));
      print_to_bt(", total image Update time = ");
      print_to_bt(String(checkpoint_3 - checkpoint_0));
      print_to_bt("\n");
      hall_sensor.printHallStats();
    }
#endif
  }
}
