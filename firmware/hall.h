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
#include "bt.h"

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************

#define PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT                        1
#define PRINT_HALL_READING_EVERY_TIME_WE_GET_ANGLE                    0

const float alpha = 0.02;
const float beta = 1 - alpha;

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
  float moving_average;
  bool did_interrupt_just_occur;

public:

  Hall (int pin_number) : pin_number(pin_number), time_of_last_detection_in_microseconds(micros()), 
                          last_period(1000000), moving_average(1000000), did_interrupt_just_occur(false) {
    pinMode(pin_number, INPUT); 
    assert(current_hall == 0);
    current_hall = this;
    attachInterrupt(digitalPinToInterrupt(pin_number), magnet_detect, RISING);
  }


  void printHallReading() {
#if PRINT_HALL_READING_EVERY_TIME_WE_GET_ANGLE
    if (micros() % 100 == 0) {
      int analog_hall_reading = analogRead(pin_number); //Read the sensor
      int digital_hall_reading = digitalRead(pin_number);
      print_to_bt("analog_hall_reading = ");
      print_to_bt(String(analog_hall_reading));
      print_to_bt("\t\t digital_hall_reading = ");
      print_to_bt(String(digital_hall_reading));
      print_to_bt("\n");
    }
#endif
  }



  void printHallLastPeriod() {
#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
    print_to_bt("last_period = ");
    print_to_bt(String(last_period));
    print_to_bt(", moving_average = ");
    print_to_bt(String(moving_average));
    print_to_bt("\n");
#endif
  }



  void magnet_detected_on_pin() {
    unsigned long new_time = micros();
    unsigned long potential_last_period = new_time - time_of_last_detection_in_microseconds;
    // protect from multiple interrupts that are very close together
    if (potential_last_period > 50000) { // no less than 50 ms (cannot handle more than 1200 rpm)
      last_period = potential_last_period;
      time_of_last_detection_in_microseconds = new_time;
      did_interrupt_just_occur = true;
    }
  }

  int get_angle() {
    printHallReading();
    if (did_interrupt_just_occur){
      did_interrupt_just_occur = false;
      moving_average = (moving_average * beta) + (last_period * alpha);
      printHallLastPeriod();
    }
    int T = (int)floor(moving_average);
    int current_delta = (micros() - time_of_last_detection_in_microseconds) % T;
    float percentage_of_circle = ((float)current_delta) / T;
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
