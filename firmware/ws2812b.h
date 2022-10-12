/// ********************************************************************************************************************
/// multiple include protection
/// ********************************************************************************************************************

#pragma once

/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

#include "matrix.h"
#include "array.h"
#include "globals.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

/// ********************************************************************************************************************
/// namespace definition
/// ********************************************************************************************************************

namespace ws2812b {

/// ********************************************************************************************************************
/// protected variable
/// ********************************************************************************************************************

namespace {
Adafruit_NeoPixel _strip(globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::PIN_NUMBER_OF_LED_STRIP_1, NEO_GRB + NEO_KHZ800);
}

/// ********************************************************************************************************************
/// functions
/// ********************************************************************************************************************

void begin() {
// These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
// Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  _strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  _strip.clear();
  Serial.println("ws2812b initialized.");
}

Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> convert_rgb_to_neopixel_rgb(const Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, 3>& v) {
  Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> res;
  for (int i = 0; i < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1; i++) {
    res.at(i) = _strip.Color(v.at(i, 0), v.at(i, 1), v.at(i, 2));
  }
  return res;
}

void update_LED(const Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1>& v) {
  for (int i = 0; i < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1; i++) {
    _strip.setPixelColor(i, v.at(i));
  }
  _strip.show();
}


}