mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

DF_CPU ?= 16000000UL
PART ?= atmega328p
MAIN_NAME ?= $(current_dir)
BUILD_DIR ?= bin
SRC_DIR ?= src
DEVICE_PORT ?= /dev/ttyACM0
BAUD_RATE ?= 115200

build:
	avr-gcc \
		-Os \
		-Wall \
		-Wextra \
		-ffreestanding \
		-DF_CPU=$(DF_CPU) \
		-mmcu=$(PART) \
		-c \
		-o $(BUILD_DIR)/$(MAIN_NAME).o \
		$(SRC_DIR)/$(MAIN_NAME).c && \
	avr-gcc \
		-DF_CPU=$(DF_CPU) \
		-mmcu=$(PART) \
		-o $(BUILD_DIR)/$(MAIN_NAME).bin $(BUILD_DIR)/$(MAIN_NAME).o && \
	avr-objcopy \
		-O ihex \
		-R .eeprom \
		$(BUILD_DIR)/$(MAIN_NAME).bin $(BUILD_DIR)/$(MAIN_NAME).hex

flash:
	avrdude \
		-F \
		-V \
		-c arduino \
		-p $(PART) \
		-P $(DEVICE_PORT) \
		-b $(BAUD_RATE) \
		-U flash:w:$(BUILD_DIR)/$(MAIN_NAME).hex

clean:
	find $(BUILD_DIR) -type f ! -name '.gitignore' -delete

printvars:
	$(info mkfile_path=$(mkfile_path))
	$(info current_dir=$(current_dir))
	$(info DF_CPU=$(DF_CPU))
	$(info PART=$(PART))
	$(info MAIN_NAME=$(MAIN_NAME))
	$(info BUILD_DIR=$(BUILD_DIR))
	$(info SRC_DIR=$(SRC_DIR))
	$(info DEVICE_PORT=$(DEVICE_PORT))
	$(info BAUD_RATE=$(BAUD_RATE))
