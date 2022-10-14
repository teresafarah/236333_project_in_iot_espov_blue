# Design

Our project is simple in terms of hardware, it needs few parts:
1. ESP32, we had the 30 pin version, but the 38 pin would work as 
   well.
2. Jumper cables.
3. Bread board (+- strip).
4. Hall sensor with digital output.
5. WS2812b LED strip (comes in multiple densities, the denser
   the better)
6. External battery.
7. Magnet.

You can find an image of how to put these together here:

![Connection Diagram](images/connection%20diagram.jpg)

# The Display

The idea is that all these parts (except the magnet) 
would be on some kind of stick, and the stick would rotate around 
an axis. each time a full revolution is finished, the hall sensor
triggers an interrupt informing the esp. The esp can then start to
estimate how long a revolution takes. That information coupled with
the knowledge of when the last interrupt was, allows the esp to 
know what angle it's on at any given moment. All that's left
to do is display the corresponding pixels in the image it's trying
to show.

Here is an image describing just that:

![The Display](images/display/display%201.jpeg)

# The App

The app communicates with the display using bluetooth,
it can take any image and resize it into the right size
(number of LEDs on display) and sends that data over to 
the display to show.

Another feature is the ability to write any message 
(including multiple languages and emojis) and send that message
to the display to show.

Here's a screenshot from the app:

![Splash Screen From App](images/app_screenshots/app%201.jpeg)


**More images can be found under images.**


# Parameters

There are some changeable parameters for the firmware, they can be found in
`globals.h` file.
