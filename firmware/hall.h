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
  unsigned long time_of_last_detection_in_milliseconds ;
  int last_period;

public:

  Hall (int pin_number) : pin_number(pin_number), time_of_last_detection_in_milliseconds(millis()), last_period(1000) {
    pinMode(pin_number, INPUT);
    assert(current_hall == 0);
    current_hall = this;
    attachInterrupt(digitalPinToInterrupt(pin_number), magnet_detect, RISING);
  }

  void printHallReading() {
    int hallVal = digitalRead(pin_number);
    Serial.println(hallVal);
  }


  void magnet_detected_on_pin() {
    Serial.println("Magnet detected!");
    unsigned long new_time = millis();
    last_period = new_time - time_of_last_detection_in_milliseconds;
    if (last_period == 0){
      last_period = 1;
    }
    time_of_last_detection_in_milliseconds = new_time;
  }

  int get_angle() {
    int current_delta = (millis() - time_of_last_detection_in_milliseconds) % last_period;
    cout << "current_delta = " << current_delta << endl;
    float percentage_of_circle = ((float)current_delta) / last_period;
    cout << "percentage_of_circle = " << percentage_of_circle << endl;
    float float_angle = percentage_of_circle * 360;
    cout << "float_angle = " << float_angle << endl;
    int angle = (float)float_angle;
    return angle;
  }

};

/// ********************************************************************************************************************
/// interrupt handler
/// ********************************************************************************************************************

void magnet_detect(){
  Serial.println("Magnet detected!");
  assert(current_hall != 0);
  current_hall->magnet_detected_on_pin();
}
