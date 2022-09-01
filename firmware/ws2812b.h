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
#include "bt.h"

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
  Adafruit_NeoPixel strip;

  
public:

  /*
   * Constructor, creates an object that manages a strip of LEDs.
   * @param pin_number, the pin on which the LED control is located.
   * @param number_of_leds, the number of LEDs that the strip has.
   */
  WS2812B(int pin_number, int number_of_leds) : pin_number(pin_number), number_of_leds(number_of_leds), 
                                                strip(number_of_leds, pin_number, NEO_GRB + NEO_KHZ800) {
    // Argument 1 = Number of pixels in NeoPixel strip
    // Argument 2 = Arduino pin number (most are valid)
    // Argument 3 = Pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
    //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
    assert(pin_number >= 0);
    assert(number_of_leds >= 0);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    strip.begin();
    strip.clear();
  }

  /*
   * Method that updates the LED strip to the desired colors.
   * @param, a vector of the same size as the LED strip, each element in this vector is another vector of size 3 
   *         containing RGB values for that LED.
   */
  void update_LED(const vector<vector<uint8_t>>& v){
    update_LED_fast(convert_rgb_to_neopixel_rgb(v));
  }

  vector<uint32_t> convert_rgb_to_neopixel_rgb(const vector<vector<uint8_t>>& v) {
    assert(v.size() == number_of_leds);
    vector<uint32_t> newv(number_of_leds);
    for(int i=0; i < number_of_leds; i++) {
      assert(v.at(i).size() == 3);
      newv.at(i) = strip.Color(v.at(i).at(0), v.at(i).at(1), v.at(i).at(2));
    }
    return newv;
  }

  void update_LED_fast(const vector<uint32_t>& v){
    assert(v.size() == number_of_leds);
    for(int i=0; i < number_of_leds; i++) {
      strip.setPixelColor(i, v.at(i));
    }
    strip.show();
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

    /*
   * Function made for testing the max brightness of the LED strip.
   */
  void perform_LED_brightness_test() {
    while (true) {
      for (uint8_t brightness = 0; brightness <= 255; brightness++){
        print_to_bt("brightness = ");
        print_to_bt(String(brightness));
        print_to_bt("\n");
        vector<vector<uint8_t>> colors;
        for(int i=0; i < number_of_leds; i++) {
          vector<uint8_t> random_rgb = {brightness, brightness, brightness};
          colors.push_back(random_rgb);
        }
        update_LED(colors);
        delay(100);
      }
    }
  }

};
