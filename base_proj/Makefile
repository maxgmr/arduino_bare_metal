mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

DF_CPU ?= 16000000UL
MMCU ?= atmega328p
MAIN_NAME ?= $(current_dir)
BUILD_DIR ?= ./build
SRC_DIR ?= ./src

default:
	avr-gcc \
		-Os \
		-DF_CPU=$(DF_CPU) \
		-mmcu=$(MMCU) \
		-c \
		-o $(BUILD_DIR)/$(MAIN_NAME).o \
		$(SRC_DIR)/$(MAIN_NAME).c
	avr-gcc \
		-DF_CPU=$(DF_CPU) \
		-mmcu=$(MMCU) \
		-o $(BUILD_DIR)/$(MAIN_NAME).bin $(BUILD_DIR)/$(MAIN_NAME).o
	avr-objcopy \
		-O ihex \
		-R .eeprom \
		$(BUILD_DIR)/$(MAIN_NAME).bin $(BUILD_DIR)/$(MAIN_NAME).hex

clean:
	find . -type f ! -name '.gitignore' -delete

printvars:
	$(info DF_CPU=$(DF_CPU))
	$(info MMCU=$(MMCU))
	$(info MAIN_C=$(MAIN_C))
	$(info mkfile_path=$(mkfile_path))
	$(info current_dir=$(current_dir))
