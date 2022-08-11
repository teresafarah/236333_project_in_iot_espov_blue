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
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// class for managing LED strips
/// ********************************************************************************************************************

class WS2812B {

  
  int pin_number;
  int number_of_leds;
  Adafruit_NeoPixel pixels;

  
public:

  /*
   * Constructor, creates an object that manages a strip of LEDs.
   * @param pin_number, the pin on which the LED control is located.
   * @param number_of_leds, the number of LEDs that the strip has.
   */
  WS2812B(int pin_number, int number_of_leds) : pin_number(pin_number), number_of_leds(number_of_leds), 
                                                pixels(number_of_leds, pin_number, NEO_GRB + NEO_KHZ800) {
    assert(pin_number >= 0);
    assert(number_of_leds >= 0);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    pixels.begin();
    pixels.clear();
  }

  /*
   * Method that updates the LED strip to the desired colors.
   * @param, a vector of the same size as the LED strip, each element in this vector is another vector of size 3 
   *         containing RGB values for that LED.
   */
  void update_LED(vector<vector<uint8_t>> v){
    assert(v.size() == number_of_leds);
    for(int i=0; i < number_of_leds; i++) {
      assert(v.at(i).size() == 3);
      pixels.setPixelColor(i, pixels.Color(v.at(i).at(0), v.at(i).at(1), v.at(i).at(2)));
    }
    pixels.show();
  }

  /*
   * Function made for testing that paint the LED strip with random colors.
   */
  void update_LED_with_random_colors() {
    vector<vector<uint8_t>> colors;
    for(int i=0; i < number_of_leds; i++) {
      vector<uint8_t> random_rgb = {rand() & 0xff, rand() & 0xff, rand() & 0xff};
      colors.push_back(random_rgb);
    }
    update_LED(colors);
  }

};
