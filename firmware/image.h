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
  int radius_in_pixels;
  int height_and_width;
  vector<vector<uint32_t>> angle_to_strip;
  
public:

  /// ******************************************************************************************************************
  /// public functions
  /// ******************************************************************************************************************

  /*
   * Constructor, creates an object that manages an image in memory.
   */
  Image(const T& led_strip_1, int number_of_pixels_on_led_strip) : led_strip_1(led_strip_1), radius_in_pixels(number_of_pixels_on_led_strip) {
    assert(0 < radius_in_pixels);
    assert(radius_in_pixels < 100); // just checking but might be more
    height_and_width = 2 * radius_in_pixels + 1; // make room for one empty pixels in the middle of the circle
    
  }

  void update_image(const vector<vector<uint8_t>>& red, const vector<vector<uint8_t>>& green, const vector<vector<uint8_t>>& blue){
    assert(check_that_image_is_square(red, green, blue));
    assert(red.size() == height_and_width);
    fill_angle_to_strip_vector(red, green, blue);
  }

  void update_image_for_testing() {
    vector<vector<uint8_t>> zeros(height_and_width);
    for (int i = 0; i < height_and_width; ++i){
      zeros.at(i) = vector<uint8_t>(height_and_width);
      for (int j = 0; j < height_and_width; j++){
        zeros.at(i).at(j) = 0;
      }
    }

    vector<vector<uint8_t>> red = zeros;
    vector<vector<uint8_t>> green = zeros;
    vector<vector<uint8_t>> blue = zeros;

    vector<vector<int>> red_positions = {
      {6,5},  {7,5},  {8,5},  {9,5},  {10,5},  {11,5},  {12,5},
      {6,6},                                            {12,6},
      {6,7},                                            {12,7},
      {6,8},                                            {12,8},
      {6,9},                                            {12,9},
      {6,10}, {7,10}, {8,10}, {9,10}, {10,10}, {11,10}, {12,10},
      {6,11},                                           {12,11},
      {6,12},                                           {12,12},
      {6,13},                                           {12,13},
      };
    for (int i = 0; i < red_positions.size(); ++i){
      int x = red_positions.at(i).at(0);
      int y = red_positions.at(i).at(1);
      red.at(x).at(y) = 255;
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
    double x0, y0, dx, dy;
    x0 = y0 = ((double)height_and_width) / 2;
    dx = cos (((double)angle_relative_to_x) * PI / 180.0 );
    dy = sin (((double)angle_relative_to_x) * PI / 180.0 );
    vector<vector<int>> result;
    for (int i = 1; i <= radius_in_pixels; ++i){
      /// floor rounds down, ceiling rounds up, and truncate rounds towards zero.
      int x = (int)trunc(x0 + (dx * i)); // can't be round since sometimes that goes out of bounds
      int y = (int)trunc(y0 + (dy * i));
      assert(0 <= x && x < height_and_width);
      assert(0 <= y && y < height_and_width);
      result.push_back({x, y});
    }
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
