# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = uno
USER_LIB_PATH = $(HOME)/Documents/code/arduino_sensor_reader
ARDUINO_LIBS += voltage
VOLTAGE_ARCHIVE = build-uno/libvoltage.a

CXXFLAGS += -Ivoltage
OTHER_OBJS = voltage/$(VOLTAGE_ARCHIVE)

include /usr/share/arduino/Arduino.mk

voltage/$(VOLTAGE_ARCHIVE):
	$(MAKE) -C voltage $(VOLTAGE_ARCHIVE)

clean::
	$(MAKE) -C voltage clean