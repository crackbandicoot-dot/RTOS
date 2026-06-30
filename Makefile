# Makefile for CMSIS-RTOS project on ARM Cortex-M3 (QEMU)

# Compiler Settings
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

# MCU and Flags
CPU = -mcpu=cortex-m3
THUMB = -mthumb
CFLAGS = $(CPU) $(THUMB) -O0 -g3 -Wall -Wextra -std=gnu11 -I./src
LDSCRIPT = src/gcc_arm.ld
LDFLAGS = $(CPU) $(THUMB) -T $(LDSCRIPT) --specs=nosys.specs -nostartfiles -Wl,-Map=kernel.map -Wl,--gc-sections

# Source files
SRCS = src/uart.c \
       src/os_kernel.c \
       src/os_interrupts.c \
	   src/start.c \
	   src/main.c 

ASRCS = src/startup_ARMCM3.S 
# Object files
OBJS = $(SRCS:.c=.o) $(ASRCS:.S=.o)
TARGET = kernel.elf

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful! Target: $(TARGET)"
	@echo "You can run this on QEMU using a command like:"
	@echo "qemu-system-arm -machine lm3s6965evb -nographic -kernel $(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) kernel.map

.PHONY: all clean
