# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    = uno
USER_LIB_PATH = $(HOME)/Documents/code/arduino_sensor_reader
ARDUINO_LIBS += Arduino-Log
LOG_ARCHIVE = build-$(BOARD_TAG)/liblog.a 

CXXFLAGS += -IArduino-Log
OTHER_OBJS = Arduino-Log/$(LOG_ARCHIVE)

include /usr/share/arduino/Arduino.mk

Arduino-Log/$(LOG_ARCHIVE):
	$(MAKE) -C Arduino-Log $(LOG_ARCHIVE)

clean::
	$(MAKE) -C Arduino-Log clean
