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
const int NUMBER_OF_LEDS_IN_LED_STRIP_1 =       71;
const int PIN_NUMBER_OF_HALL_SENSOR =           4;

#define PRINT_TIME_OF_LED_UPDATE                               0

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
      Serial.print("Theta calculation time = ");
      Serial.print(checkpoint_1 - checkpoint_0);
      Serial.print(", LED vector finding time = ");
      Serial.print(checkpoint_2 - checkpoint_1);
      Serial.print(", updating LED time = ");
      Serial.print(checkpoint_3 - checkpoint_2);
      Serial.print(", total image Update time = ");
      Serial.println(checkpoint_3 - checkpoint_0);      
    }
#endif
  }
}
