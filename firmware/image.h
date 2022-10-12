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
#include <cmath>

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

using namespace std;

/// ********************************************************************************************************************
/// constants
/// ********************************************************************************************************************


/// ********************************************************************************************************************
/// class for managing an image in memory
/// ********************************************************************************************************************

template <class T>
class Image {

  /// ******************************************************************************************************************
  /// private variables
  /// ******************************************************************************************************************

  T led_strip_1;
  int diameter_in_pixels;
  vector<vector<uint32_t>> angle_to_strip;
  
public:

  /// ******************************************************************************************************************
  /// public functions
  /// ******************************************************************************************************************

  /*
   * Constructor, creates an object that manages an image in memory.
   */
  Image(const T& led_strip_1, int number_of_pixels_on_led_strip) : led_strip_1(led_strip_1), diameter_in_pixels(number_of_pixels_on_led_strip) {
    assert(0 < diameter_in_pixels);
    assert(diameter_in_pixels < 100); // just checking but might be more
    assert(diameter_in_pixels % 2 == 1); // extremely messy to calculate when number of pixels is not uneven
  }

  void update_image(const vector<vector<uint8_t>>& red, const vector<vector<uint8_t>>& green, const vector<vector<uint8_t>>& blue){
    assert(check_that_image_is_square(red, green, blue));
    assert(red.size() == diameter_in_pixels);
    fill_angle_to_strip_vector(red, green, blue);
  }

  vector<vector<uint8_t>> get_zeros_image() {
    vector<vector<uint8_t>> zeros(diameter_in_pixels);
    for (int i = 0; i < diameter_in_pixels; ++i){
      zeros.at(i) = vector<uint8_t>(diameter_in_pixels);
      for (int j = 0; j < diameter_in_pixels; j++){
        zeros.at(i).at(j) = 0;
      }
    }
    return zeros;
  }

  void update_image_for_testing() {
    vector<vector<uint8_t>> zeros = get_zeros_image();
    vector<vector<uint8_t>> red = zeros;
    vector<vector<uint8_t>> green = zeros;
    vector<vector<uint8_t>> blue = zeros;

    for (int i = 0; i < diameter_in_pixels; ++i){
      for (int j = 0; j < diameter_in_pixels; ++j){
        if (i % 5 == 0){
          if (i % 3 == 0){
            red.at(i).at(j) = 255;
          } else if (i % 3 == 1) {
            green.at(i).at(j) = 255;
          } else {
            blue.at(i).at(j) = 255;
          }
        }
      }
    }
    
    update_image(red, green, blue);
  }

  void update_image_as_a_vector_of_bytes(const vector<byte>& img) {
    assert(img.size() == diameter_in_pixels * diameter_in_pixels * 3);
    vector<vector<uint8_t>> zeros = get_zeros_image();
    vector<vector<uint8_t>> red = zeros;
    vector<vector<uint8_t>> green = zeros;
    vector<vector<uint8_t>> blue = zeros;

    int index = 0;
    for (int color = 0; color < 3; color++){
      for (int i = 0; i < diameter_in_pixels; ++i){
        for (int j = 0; j < diameter_in_pixels; ++j){
          if (color == 0){
            red.at(i).at(j) = img.at(index);
          } else if (color == 1) {
            green.at(i).at(j) = img.at(index);
          } else {
            blue.at(i).at(j) = img.at(index);
          }
          index ++;
        }
      }
    }
    update_image(red, green, blue);
  }

  vector<uint32_t>& get_led_strip_colors(int angle_relative_to_x){
    return angle_to_strip.at(angle_relative_to_x);
  }

private:

  /// ******************************************************************************************************************
  /// private helper functions
  /// ******************************************************************************************************************

  bool check_that_image_is_square(const vector<vector<uint8_t>>& n_red, const vector<vector<uint8_t>>& n_green, const vector<vector<uint8_t>>& n_blue){
    int potential_height_and_width = n_red.size();
    assert(n_red.size() == n_green.size());
    assert(n_red.size() == n_blue.size());
    for (int i = 0; i < potential_height_and_width; ++i){
      assert(n_red.at(i).size() == potential_height_and_width);
      assert(n_green.at(i).size() == potential_height_and_width);
      assert(n_blue.at(i).size() == potential_height_and_width);
    }
    return true;
  }

  vector<vector<int>> get_relavent_positions(int angle_relative_to_x){
    double x0 = ((double)diameter_in_pixels) / 2;
    double y0 = x0;
    double dx = cos (((double)angle_relative_to_x) * PI / 180.0 );
    double dy = sin (((double)angle_relative_to_x) * PI / 180.0 );
    vector<vector<int>> result;
    int from = -(diameter_in_pixels / 2);
    int to = (diameter_in_pixels / 2);
    for (int i = from; i <= to ; ++i){
      double x_as_real_number = x0 + (dx * i);
      double y_as_real_number = y0 + (dy * i);
      /// floor rounds down, ceiling rounds up, and truncate rounds towards zero.
      int x = (int)floor(x_as_real_number); // can't be round since sometimes that goes out of bounds
      int y = (int)floor(y_as_real_number);
      assert(0 <= x && x < diameter_in_pixels);
      assert(0 <= y && y < diameter_in_pixels);
      result.push_back({x, y});
    }
    assert(result.size() == diameter_in_pixels);
    return result;
  }

  vector<uint32_t> calculate_led_strip_colors(int angle_relative_to_x, const vector<vector<uint8_t>>& red, const vector<vector<uint8_t>>& green, const vector<vector<uint8_t>>& blue){
    assert(0 <= angle_relative_to_x && angle_relative_to_x < 360);
    vector<vector<int>> positions = get_relavent_positions(angle_relative_to_x);
    
    vector<vector<uint8_t>> result_as_rgb;
    for (vector<int>& pos: positions) {
      assert(pos.size() == 2);
      int x = pos.at(0);
      int y = pos.at(1);
      result_as_rgb.push_back({red.at(x).at(y), green.at(x).at(y), blue.at(x).at(y)});
    }

    vector<uint32_t> result = led_strip_1.convert_rgb_to_neopixel_rgb(result_as_rgb);
    return result;
  }

  void fill_angle_to_strip_vector(const vector<vector<uint8_t>>& red, const vector<vector<uint8_t>>& green, const vector<vector<uint8_t>>& blue){
    angle_to_strip = vector<vector<uint32_t>>(360);
    for (int theta = 0; theta < 360; ++theta){
      angle_to_strip.at(theta) = calculate_led_strip_colors(theta, red, green, blue);
    }
  }

  
};
