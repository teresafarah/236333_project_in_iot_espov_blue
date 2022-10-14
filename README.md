# Introduction

This code is for a project in internet of things as part of
a university course. The project is to make a persistence
of vision display, which is a display that uses our eyes'
ability to fill in gaps when it comes to fast moving object.

# About Us

We are three students studying at the 
Technion - Israel Institute of Technology at the faculty of 
computer science, our names are:

- Mustafa Hijazi
- Teresa Farah
- Andrew Luka

The course that this project is a part of is 236333 - project
in IOT. The course is a part od the ICST lab at the faculty.

# Repository Layout

This repository is split into 2 parts:

1. Firmware: This is the code that sits on the esp32
   (a more powerful arduino alternative), it houses code that 
   manages the display, and updates the spinning LEDs. The code
   for the firmware sits in the **firmware** folder.
2. Application: This is the code for the flutter application 
   that sits on your phone, the app communicates with the 
   display using bluetooth. The code for the app sits in the
   **flutter** folder.

# Libraries

For the project we used a few esp32 libraries, these are:


| Library           | By                | Version | Function                                               |
|-------------------|-------------------|---------|--------------------------------------------------------|
| Adafruit_NeoPixel | Adafruit          | 1.10.6  | Manages writing to the LEDs                            |
| esp32             | Espressif Systems | 1.0.6   | Allows working with esp32 and contains BluetoothSerial |

# Documentation

Further documentation and images can be found in the folder named 
**documentation**.

[Link to DESIGN document](documentation/DESIGN.md)

## License

MIT

