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
#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
  bool to_print;
#endif

public:

  Hall (int pin_number) : pin_number(pin_number), time_of_last_detection_in_microseconds(micros()), last_period(1000000) {
#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
    to_print = false;
#endif
    pinMode(pin_number, INPUT); 
//    analogSetPinAttenuation(pin_number, ADC_2_5db);
    assert(current_hall == 0);
    current_hall = this;
    attachInterrupt(digitalPinToInterrupt(pin_number), magnet_detect, RISING);
  }

#if PRINT_HALL_READING_EVERY_TIME_WE_GET_ANGLE
  void printHallReading() {
    int analog_hall_reading = analogRead(pin_number); //Read the sensor
    int digital_hall_reading = digitalRead(pin_number);
    Serial.print("analog_hall_reading = ");
    Serial.print(analog_hall_reading);
    Serial.print("\t\t digital_hall_reading = ");
    Serial.println(digital_hall_reading);
  }
#endif

#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
  void printHallLastPeriod() {
    Serial.print("last_period = ");
    Serial.println(last_period);
    print_to_bt("last_period = ");
    String thisString = String(last_period);
    print_to_bt(thisString);
    print_to_bt("\n");
  }
#endif


  void magnet_detected_on_pin() {
    unsigned long new_time = micros();
    unsigned long potential_last_period = new_time - time_of_last_detection_in_microseconds;
    // protect from multiple interrupts that are very close together
    if (potential_last_period > 20) {
      last_period = new_time - time_of_last_detection_in_microseconds;
      time_of_last_detection_in_microseconds = new_time;
#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
      to_print = true;
#endif
    }
  }

  int get_angle() {
#if PRINT_HALL_READING_EVERY_TIME_WE_GET_ANGLE
  if (micros() % 100 == 0) { // with prob 1 / 100
    printHallReading();
  }
#endif
#if PRINT_LAST_PERIOD_TIME_AFTER_INTERRUPT
    if (to_print){
      to_print = false;
      printHallLastPeriod();
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
