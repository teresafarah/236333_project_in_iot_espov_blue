/// ********************************************************************************************************************
/// multiple include protection
/// ********************************************************************************************************************

#pragma once

/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#include <vector>
#include <cassert>
#include <iostream>

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************

#define PERIOD_TIME_TEST                        0

/// ********************************************************************************************************************
/// Foward declarations
/// ********************************************************************************************************************

void magnet_detect();
class Hall;

/// ********************************************************************************************************************
/// global Hall
/// ********************************************************************************************************************

Hall* current_hall = 0;

/// ********************************************************************************************************************
/// class for managing LED strips
/// ********************************************************************************************************************

class Hall {
  
  int pin_number;
  unsigned long time_of_last_detection_in_microseconds ;
  unsigned long last_period;
#if PERIOD_TIME_TEST
  bool to_print;
#endif

public:

  Hall (int pin_number) : pin_number(pin_number), time_of_last_detection_in_microseconds(micros()), last_period(1000000) {
#if PERIOD_TIME_TEST
    to_print = false;
#endif
    pinMode(pin_number, INPUT);
    assert(current_hall == 0);
    current_hall = this;
    attachInterrupt(digitalPinToInterrupt(pin_number), magnet_detect, RISING);
  }

  void printHallReading() {
    cout << " last_period = " << last_period << "\n";
  }


  void magnet_detected_on_pin() {
    unsigned long new_time = micros();
    last_period = new_time - time_of_last_detection_in_microseconds;
    time_of_last_detection_in_microseconds = new_time;
#if PERIOD_TIME_TEST
    to_print = true;
#endif
  }

  int get_angle() {
#if PERIOD_TIME_TEST
    if (to_print){
      to_print = false;
      printHallReading();
    }
#endif
    if (last_period == 0){
      last_period = 1;
    }
    int current_delta = (micros() - time_of_last_detection_in_microseconds) % last_period;
    float percentage_of_circle = ((float)current_delta) / last_period;
    float float_angle = percentage_of_circle * 360;
    int angle = (float)float_angle;
    return angle;
  }

};

/// ********************************************************************************************************************
/// interrupt handler
/// ********************************************************************************************************************

void magnet_detect(){
  assert(current_hall != 0);
  current_hall->magnet_detected_on_pin();
}
