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

class Image {

  /// ******************************************************************************************************************
  /// private variables
  /// ******************************************************************************************************************
  
  int height_and_width;
  vector<vector<uint8_t>> red;
  vector<vector<uint8_t>> green;
  vector<vector<uint8_t>> blue;
  vector<vector<vector<uint8_t>>> angle_to_strip;

  /// ******************************************************************************************************************
  /// private helper functions
  /// ******************************************************************************************************************

  bool check_rgb_values(vector<vector<uint8_t>> n_red, vector<vector<uint8_t>> n_green, vector<vector<uint8_t>> n_blue){
    assert(3 < n_red.size());
    assert(n_red.size() < 500);
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

  vector<vector<int>> get_relavent_positions(int angle_relative_to_x, int number_of_pixels){
    double x0, y0, dx, dy;
    x0 = y0 = ((double)height_and_width) / 2;
    dx = cos (((double)angle_relative_to_x) * PI / 180.0 );
    dy = sin (((double)angle_relative_to_x) * PI / 180.0 );
//    cout << "x0, y0, dx, dy = " << x0 << ", " << y0 << ", " << dx << ", " << dy << endl;
    vector<vector<int>> result;
    for (int i = 1; i <= number_of_pixels; ++i){
      /// floor rounds down, ceiling rounds up, and truncate rounds towards zero.
      int x = (int)trunc(x0 + (dx * i)); // can't be round since sometimes that goes out of bounds
      int y = (int)trunc(y0 + (dy * i));
      assert(0 <= x && x < height_and_width);
      assert(0 <= y && y < height_and_width);
      result.push_back({x, y});
    }
    return result;
  }

  vector<vector<uint8_t>> calculate_led_strip_colors(int angle_relative_to_x, int number_of_pixels){
    assert(number_of_pixels <= (height_and_width / 2));
    assert(0 <= angle_relative_to_x && angle_relative_to_x < 360);
    vector<vector<int>> positions = get_relavent_positions(angle_relative_to_x, number_of_pixels);
    
//    cout << "length of positions = " << positions.size() << endl;
//    for (int i = 0; i < positions.size(); ++i){
//      assert(positions.at(i).size() == 2);
//      cout << "position[" << i << "] = (" << positions.at(i).at(0) << ", " << positions.at(i).at(1) << ")" << endl;
//    }
    
    assert(positions.size() == number_of_pixels);
    vector<vector<uint8_t>> result;
    for (vector<int>& pos: positions) {
      assert(pos.size() == 2);
      int x = pos.at(0);
      int y = pos.at(1);
      result.push_back({red.at(x).at(y), green.at(x).at(y), blue.at(x).at(y)});
    }
    return result;
  }

  void fill_angle_to_strip_vector(){
    for (int theta = 0; theta < 360; ++theta){
      angle_to_strip.push_back(calculate_led_strip_colors(theta, height_and_width / 2));
    }
  }

  
public:

  /// ******************************************************************************************************************
  /// public functions
  /// ******************************************************************************************************************

  /*
   * Constructor, creates an object that manages an image in memory.
   */
  Image() {
  }

  void update_image(vector<vector<uint8_t>> n_red, vector<vector<uint8_t>> n_green, vector<vector<uint8_t>> n_blue){
    assert(check_rgb_values(n_red, n_green, n_blue));
    red = n_red;
    green = n_green;
    blue = n_blue;
    height_and_width = red.size();
    fill_angle_to_strip_vector();
  }

  void update_image_for_testing() {
    update_image(
      {
        {255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      },
      {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      }
    );
  }

  vector<vector<uint8_t>> get_led_strip_colors(int angle_relative_to_x, int number_of_pixels){
    vector<vector<uint8_t>>& cached_vec = angle_to_strip.at(angle_relative_to_x);
    return vector<vector<uint8_t>>(cached_vec.begin(), cached_vec.begin() + number_of_pixels);
  }
};
