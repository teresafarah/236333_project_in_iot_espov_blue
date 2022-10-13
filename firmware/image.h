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
#include <cassert>
#include <iostream>
#include <cmath>

/// ********************************************************************************************************************
/// namespace definition
/// ********************************************************************************************************************

namespace image {

/// ********************************************************************************************************************
/// protected variable
/// ********************************************************************************************************************

namespace {
Matrix<uint32_t, globals::NUM_OF_ANGLES, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> _angle_to_strip;

// these are used to update image
Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> _red;
Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> _green;
Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> _blue;
int _current_byte;
}

void clear_pending_image() {
  Serial.println("Called clear_pending_image.");
  _current_byte = 0;
}

void begin() {
  Serial.println("image initialized.");
  clear_pending_image();
  // Serial.print("globals::SINGLE_COLOR_SIZE_IN_BYTES = ");
  // Serial.println(globals::SINGLE_COLOR_SIZE_IN_BYTES);
}

Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> get_zeros_image() {
  Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> zeros;
  for (int i = 0; i < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1; ++i) {
    for (int j = 0; j < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1; j++) {
      zeros.at(i, j) = 0;
    }
  }
  return zeros;
}

const Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1>& get_led_strip_colors(int angle_relative_to_x) {
  return _angle_to_strip.get_row(angle_relative_to_x / globals::DISTANCE_BETWEEN_ANGLES);
}

Matrix<int, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, 2> get_relavent_positions(int angle_relative_to_x) {
  // Serial.print("Calling get_relavent_positions with angle_relative_to_x = ");
  // Serial.println(angle_relative_to_x);
  double x0 = ((double)globals::NUMBER_OF_LEDS_IN_LED_STRIP_1) / 2;
  double y0 = x0;
  double dx = cos(((double)angle_relative_to_x) * PI / 180.0);
  double dy = sin(((double)angle_relative_to_x) * PI / 180.0);
  Matrix<int, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, 2> result;
  int from = -(globals::NUMBER_OF_LEDS_IN_LED_STRIP_1 / 2);
  int to = (globals::NUMBER_OF_LEDS_IN_LED_STRIP_1 / 2);
  for (int i = from; i <= to; ++i) {
    double x_as_real_number = x0 + (dx * i);
    double y_as_real_number = y0 + (dy * i);
    /// floor rounds down, ceiling rounds up, and truncate rounds towards zero.
    int x = (int)floor(x_as_real_number);  // can't be round since sometimes that goes out of bounds
    int y = (int)floor(y_as_real_number);
    assert(0 <= x && x < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1);
    assert(0 <= y && y < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1);
    result.at(i - from, 0) = x;
    result.at(i - from, 1) = y;
  }
  // Serial.print("Calling get_relavent_positions with angle_relative_to_x = ");
  // Serial.println(angle_relative_to_x);
  return result;
}

Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> calculate_led_strip_colors(int angle_relative_to_x) {
  // Serial.print("Calling calculate_led_strip_colors with angle_relative_to_x = ");
  // Serial.println(angle_relative_to_x);

  assert(0 <= angle_relative_to_x && angle_relative_to_x < 360);
  Matrix<int, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, 2> positions = get_relavent_positions(angle_relative_to_x);

  // vector<vector<uint8_t>> result_as_rgb;
  Matrix<uint8_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1, 3> result_as_rgb;
  for (int i = 0; i < globals::NUMBER_OF_LEDS_IN_LED_STRIP_1; ++i) {
    int x = positions.at(i, 0);
    int y = positions.at(i, 1);
    result_as_rgb.at(i, 0) = _red.at(x, y);
    result_as_rgb.at(i, 1) = _green.at(x, y);
    result_as_rgb.at(i, 2) = _blue.at(x, y);
  }

  Array<uint32_t, globals::NUMBER_OF_LEDS_IN_LED_STRIP_1> result = ws2812b::convert_rgb_to_neopixel_rgb(result_as_rgb);
  return result;
}

void fill_angle_to_strip_vector() {
  for (int theta = 0; theta < 360; theta += globals::DISTANCE_BETWEEN_ANGLES) {
    _angle_to_strip.get_row(theta / globals::DISTANCE_BETWEEN_ANGLES) = calculate_led_strip_colors(theta);
  }
}

void update_image() {
  Serial.println("Image is starting update...");
  fill_angle_to_strip_vector();
  Serial.println("Image update done!");
}

void update_image_for_testing() {
  Serial.println("calling update_image_for_testing.");
  auto zeros = get_zeros_image();
  _red = zeros;
  _green = zeros;
  _blue = zeros;

  const uint8_t app_color_red = 121;
  const uint8_t app_color_green = 214;
  const uint8_t app_color_blue = 221;

  const int number_of_pixels = 384;
  uint8_t i_positions[384] = { 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42 };
  uint8_t j_positions[384] = { 7, 8, 9, 10, 11, 12, 13, 14, 19, 20, 21, 22, 23, 24, 27, 28, 29, 30, 31, 32, 39, 40, 41, 42, 47, 48, 55, 56, 7, 8, 9, 10, 11, 12, 13, 14, 19, 20, 21, 22, 23, 24, 27, 28, 29, 30, 31, 32, 39, 40, 41, 42, 47, 48, 55, 56, 7, 8, 17, 18, 27, 28, 33, 34, 37, 38, 43, 44, 47, 48, 55, 56, 7, 8, 17, 18, 27, 28, 33, 34, 37, 38, 43, 44, 47, 48, 55, 56, 7, 8, 9, 10, 11, 12, 19, 20, 21, 22, 27, 28, 29, 30, 31, 32, 37, 38, 43, 44, 49, 50, 53, 54, 7, 8, 9, 10, 11, 12, 19, 20, 21, 22, 27, 28, 29, 30, 31, 32, 37, 38, 43, 44, 49, 50, 53, 54, 7, 8, 23, 24, 27, 28, 37, 38, 43, 44, 49, 50, 53, 54, 7, 8, 23, 24, 27, 28, 37, 38, 43, 44, 49, 50, 53, 54, 7, 8, 9, 10, 11, 12, 13, 14, 17, 18, 19, 20, 21, 22, 27, 28, 39, 40, 41, 42, 51, 52, 7, 8, 9, 10, 11, 12, 13, 14, 17, 18, 19, 20, 21, 22, 27, 28, 39, 40, 41, 42, 51, 52, 13, 14, 15, 16, 17, 18, 23, 24, 33, 34, 39, 40, 43, 44, 45, 46, 47, 48, 49, 50, 13, 14, 15, 16, 17, 18, 23, 24, 33, 34, 39, 40, 43, 44, 45, 46, 47, 48, 49, 50, 13, 14, 19, 20, 23, 24, 33, 34, 39, 40, 43, 44, 13, 14, 19, 20, 23, 24, 33, 34, 39, 40, 43, 44, 13, 14, 15, 16, 17, 18, 23, 24, 33, 34, 39, 40, 43, 44, 45, 46, 47, 48, 13, 14, 15, 16, 17, 18, 23, 24, 33, 34, 39, 40, 43, 44, 45, 46, 47, 48, 13, 14, 19, 20, 23, 24, 33, 34, 39, 40, 43, 44, 13, 14, 19, 20, 23, 24, 33, 34, 39, 40, 43, 44, 13, 14, 15, 16, 17, 18, 23, 24, 25, 26, 27, 28, 29, 30, 35, 36, 37, 38, 43, 44, 45, 46, 47, 48, 49, 50, 13, 14, 15, 16, 17, 18, 23, 24, 25, 26, 27, 28, 29, 30, 35, 36, 37, 38, 43, 44, 45, 46, 47, 48, 49, 50 };


  for (int k = 0; k < number_of_pixels; ++k) {
    int i = i_positions[k];
    int j = j_positions[k];
    _red.at(i, j) = app_color_red;
    _green.at(i, j) = app_color_green;
    _blue.at(i, j) = app_color_blue;
  }


  update_image();
}

void update_image_byte_by_byte(uint8_t byte) {
  int color = _current_byte / globals::SINGLE_COLOR_SIZE_IN_BYTES;
  assert(color == 0 || color == 1 || color == 2);
  int i = (_current_byte % globals::SINGLE_COLOR_SIZE_IN_BYTES) / globals::NUMBER_OF_LEDS_IN_LED_STRIP_1;
  int j = (_current_byte % globals::SINGLE_COLOR_SIZE_IN_BYTES) % globals::NUMBER_OF_LEDS_IN_LED_STRIP_1;

  if (color == 0) {
    _red.at(i, j) = byte;
  } else if (color == 1) {
    _green.at(i, j) = byte;
  } else {
    _blue.at(i, j) = byte;
  }

  _current_byte++;

  if (_current_byte == globals::IMAGE_SIZE_IN_BYTES) {
    update_image();
    clear_pending_image();
  }
}

}