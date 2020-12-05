### OS variables
UNAME_S := $(shell uname -s)

### ARDUINO_LIBS
### These are the Arduino libraries you want to use
ARDUINO_LIBS += Wire
ARDUINO_LIBS += SoftwareSerial

ARDUINO_LIBS += External/OneWire-2.3.5
ARDUINO_LIBS += External/DallasTemperature-3.9.0
ARDUINO_LIBS += External/MagneticSensorLSM303-1.0
ARDUINO_LIBS += External/Vector-1.2.0
ARDUINO_LIBS += External/RosserialArduino-0.7.9
ARDUINO_LIBS += External/TinyGPS-13.0.0
ARDUINO_LIBS += External/MemoryFree-a2d60bd
ARDUINO_LIBS += External/ArduinoPIDLibrary-1.2.0
ARDUINO_LIBS += External/lsm303-arduino-3.0.1

ARDUINO_LIBS += . # relative offsets are used for internal libraries

ARDUINO_LIBS += Common
ARDUINO_LIBS += Sensors
ARDUINO_LIBS += Actuators
ARDUINO_LIBS += Controllers
ARDUINO_LIBS += Interfaces
ARDUINO_LIBS += Sandbox
ARDUINO_LIBS += Logic

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH    :=  $(realpath ../Libraries)

### PROJECT_DIR
### This is the path to where you have created/cloned your project
PROJECT_DIR       = $(realpath .)

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ifeq ($(UNAME_S),Linux)
    ARDMK_DIR         = /usr/share/arduino
endif
ifeq ($(UNAME_S),Darwin)
    ARDMK_DIR         = /usr/local/Cellar/arduino-mk/1.6.0
endif

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
### On OS X:
#ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java
### or on Linux: (remove the one you don't want)
ifeq ($(UNAME_S),Linux)
    ARDUINO_DIR       = /usr/share/arduino
endif
ifeq ($(UNAME_S),Darwin)
    ARDUINO_DIR       = /Applications/Arduino.app/Contents/Java
endif

### BOARD_TAG
### It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
BOARD_TAG             = mega
BOARD_SUB             = atmega2560

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 115200

### AVR_TOOLS_DIR
### Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
### On OS X with `homebrew`:
#AVR_TOOLS_DIR     = /usr/local
### or on Linux: (remove the one you don't want)
ifeq ($(UNAME_S),Linux)
    #AVR_TOOLS_DIR     = /usr
endif
ifeq ($(UNAME_S),Darwin)
    AVR_TOOLS_DIR     = /usr/local
endif

### AVRDUDE
### Path to avrdude directory.
### On OS X with `homebrew`:
#AVRDUDE          = /usr/local/bin/avrdude
### or on Linux: (remove the one you don't want)
ifeq ($(UNAME_S),Linux)
    AVRDUDE          = /usr/bin/avrdude
endif
ifeq ($(UNAME_S),Darwin)
    AVRDUDE          = /usr/local/bin/avrdude
endif

### CFLAGS_STD
### Set the C standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cflags_std)
CFLAGS_STD        = -std=gnu11

### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
CXXFLAGS_STD      = -std=gnu++11

### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         += -Wall -Wextra -Werror -g
CXXFLAGS		+= -Wno-deprecated-declarations -D__PROG_TYPES_COMPAT__ -Wno-stringop-truncation -Wno-restrict -Wno-sized-deallocation -Wno-switch -Wno-implicit-fallthrough # just to get the bloody external libraries to work..

### MONITOR_PORT
### The port your board is connected to. Using an '*' tries all the ports and finds the right one.
ifeq ($(UNAME_S),Linux)
    MONITOR_PORT      = /dev/ttyACM1
endif
ifeq ($(UNAME_S),Darwin)
    MONITOR_PORT      = /dev/*.usbmodem*
endif

### CURRENT_DIR
### Do not touch - used for binaries path
CURRENT_DIR       = $(shell basename $(CURDIR))

### OBJDIR
### This is where you put the binaries you just compile using 'make'
OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

### Do not touch - the path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk
