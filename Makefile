# Makefile for STM32F103C8T6

# Toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Target
TARGET  = blink
BUILD   = build
LIBDIR  = library

# Source files
SRCS = \
	main.c \
	startup_stm32f103c8t6.c \
	$(LIBDIR)/SYSCLK.c \
	$(LIBDIR)/GPIO.c \
	$(LIBDIR)/UART.c

# Object files (mapped into build/)
OBJS = $(SRCS:%.c=$(BUILD)/%.o)

# Include paths
INCLUDES = -I$(LIBDIR)

# Compiler flags
CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O2 -g
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += $(INCLUDES)

# Linker flags
LDFLAGS  = -mcpu=cortex-m3 -mthumb -nostdlib
LDFLAGS += -T STM32F103C8T6.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD)/$(TARGET).map

# Default target
all: $(BUILD)/$(TARGET).bin

# Create build directories
$(BUILD):
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/$(LIBDIR)

# Compile C files
$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

# Create binary
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Flash using OpenOCD
flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
	-c "program $< verify reset exit"

# Clean
clean:
	rm -rf $(BUILD)

.PHONY: all flash clean