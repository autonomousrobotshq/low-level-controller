# low-level-controller

Everything coding related to the low-level-controller (Arduino).

## History

This is the OG work of autonomousrobotshq. Accept no substitution.

This repo was scrobbled together fast and without much knowledge of good practice. We're all learning.

Whomever takes this over; you might want to convert this repo to PlatformIO since that will make your life a lot easier.
You also might want to take up continuous integration tests. To confirm that nothing breaks along the way. PlatformIO provides that.

You can contact @s-t-a-n for some help with this. Alternatively you could have a look at [krakakai/Spine](https://github.com/krakakai/spine), the totally overengineered successor of this library.

## Prerequisites

1. A Unix computer (you might get Windows to work, if you are crazy enough)

2. An Arduino (mega 2560 is recommended)

## How to build

1. Install the packages from [requirements.md](./requirements.md).

2. Copy LLC1/launch.cpp.example to LLC1/launch.cpp.

3. Make sure that `BOARD_TAG` and `BOARD_SUB` match your desired platform (preconfigured for Arduino Mega 2560)

4. Run `make` in LLC1 folder to build. You likely see errors on your first compile. Don't worry, just make sure you have the right packages.

5. Make sure that `MONITOR_PORT` matches in LLC1/Makefile. An easy way to do this is to enter the Arduino IDE and check the ports there.

6. Run `make upload` in LLC1 folder to upload to Arduino.

7. Run `make monitor` in LLC1 folder to monitor the serial port. There are nicer alternatives. For example: check `screen` or use the Arduino IDE.

## A word from Stalin himself:

1. naming convention : https://guiquanz.gitbooks.io/google-cc-style-guide/content/ebook/Naming.html

2. general styleguide: https://google.github.io/styleguide/cppguide.html

3. follow existing naming convention when creating branches.

4. follow existing name/access/setting/etc styling.

5. libraries which are not important for including a header should not be included in the header but in the .cpp file.

6. every class that reads from an input should have an 'update' function in which data is polled/retreived. Getter functions only serve to access variables.

7. external libraries must be appended by their version number.

8. when using code from a remote source make sure to comply to their licensing (include license if necessary).

9. run 'clang-format -style=webkit -i [FILENAME]' before pushing.

10. don't push code that doesn't compile ('git stash' is for that).

11. commit messages should convey clearly what has changed and should contain relevant filenames.

Trespassers will be met with resistance.
