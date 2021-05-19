# laserPointer

This project will be about driving 2 servos and 1 laser using a esp32 and a power supply to to point to parts or tools, I own around my garage. This project will be connected to another project called [GParts](https://github.com/guttih/gparts) which is also located on this github space.

## How to wire
Follow [this link](./docs/wiring.md) to view wiring diagram.

## Development

To upload this program firmware over the air (OTA) change the `upload-port` to **3232**.  To upload this program firmware using usb change the `upload-port` to something like **COM6**, that is if you computer gave the esp32 usb connection the name COM6.


## Available commands

### Get commands 

#### Move

move accepts four query parameters
 1. __tilt__ is a _Required_ parameter for how much in degrees the tower should
    be tilted (up/down position).
    - Valid values: 0 - 264.
 2. __pan__ is a _Required_ parameter for how much in degrees the tower should
    be paned (left/right position).
    - Valid values: 0 - 255
 3. __laser__ is a _Optional_ parameter for how bright the laser should be where
    255 is full on and 0 if off.
    - Valid values: 0 - 255 
 4. __blink__ is a _Optional_ parameter how many milliseconds should pass before
    blinking.  Pass 0 to turn blinking off. Pass 3500 to make the laser blink
    every 3.5 seconds.
    - Valid values:  0 - 2147483647

#### Set

set accepts two query parameters
 1. __laser__ is a _Optional_ parameter for how bright the laser should be where
    255 is full on and 0 if off.
    - Valid values: 0 - 255 
 2. __blink__ is a _Optional_ parameter how many milliseconds should pass before
    blinking.  Pass 0 to turn blinking off. Pass 3500 to make the laser blink
    every 3.5 seconds.
    - Valid values:  0 - 2147483647
 