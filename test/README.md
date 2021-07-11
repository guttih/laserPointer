# Tests

These are the standard tests provided by PlatformIO.  These tests run on the
device. More information about [PlatformIO Unit Testing].

### About this Directory

This directory is intended for PlatformIO Unit Testing and project tests.

Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

More information about PlatformIO Unit Testing:
- https://docs.platformio.org/page/plus/unit-testing.html


__Running the tests__

Assuming the esp32 is connected to the usb on port COM4
```
pio test -e esp32dev --test-port COM4
```


[PlatformIO Unit Testing]:https://docs.platformio.org/page/plus/unit-testing.html