#pragma once

namespace globals {

const int PIN_NUMBER_OF_LED_STRIP_1 = 15;
const int NUMBER_OF_LEDS_IN_LED_STRIP_1 = 63;
const int PIN_NUMBER_OF_HALL_SENSOR = 4;
const int IMAGE_SIZE_IN_BYTES = (NUMBER_OF_LEDS_IN_LED_STRIP_1 * NUMBER_OF_LEDS_IN_LED_STRIP_1 * 3);
const int SINGLE_COLOR_SIZE_IN_BYTES = (NUMBER_OF_LEDS_IN_LED_STRIP_1 * NUMBER_OF_LEDS_IN_LED_STRIP_1);

const float ALPHA = 0.01;  // moving average weight, the smaller the number the slower the average moves
const float BETA = 1 - ALPHA;

// number of angles
const int NUM_OF_ANGLES = 180;
const int DISTANCE_BETWEEN_ANGLES = 2;

// period calculation
const float MAX_PERIOD_TIME_IN_MICRO_SEC = 300000;
}