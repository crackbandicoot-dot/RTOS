.PHONY: all run gdbserver gdb help clean test_runner core_tests run-rtos-tests

BINARY := cm3.elf
MACHINE := lm3s6965evb

# Variable with ?= assignment can be redefined when the makefile is called:
# make TOOLCHAIN= QEMU_PATH= will update the variable of the Makefile

CMSIS ?= ./CMSIS_5

QEMU_COMMAND := qemu-system-arm

QEMU_RUN_COMMAND := $(QEMU_COMMAND) \
  -machine $(MACHINE) \
  -cpu cortex-m3 \
  -m 4096 \
  -nographic \
  -semihosting \
  --semihosting-config enable=on,target=native \
  -serial mon:stdio \
  -device loader,file=$(BINARY) \
  -machine accel=tcg

BINARY_OBJDUMP := objdump.txt

CROSS_COMPILE = $(TOOLCHAIN)arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
GDB ?= gdb-multiarch
OBJ = $(CROSS_COMPILE)objdump

LINKER_SCRIPT = gcc_arm.ld

SRC_ASM = $(CMSIS)/Device/ARM/ARMCM3/Source/GCC/startup_ARMCM3.S
SRC_C   = $(CMSIS)/Device/ARM/ARMCM3/Source/system_ARMCM3.c 

## Source files
SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)

INCLUDE_FLAGS = \
  -I$(CMSIS)/Device/ARM/ARMCM3/Include \
  -I$(CMSIS)/CMSIS/Core/Include \
  -I.

CFLAGS = \
  -mcpu=cortex-m3 \
  -specs=nano.specs \
  -specs=nosys.specs \
  -specs=rdimon.specs \
  -Wall \
  -g3 \
  $(INCLUDE_FLAGS) \
  -mthumb \
  -nostartfiles \
  -fdata-sections \
  -ffunction-sections \
  -Wl,--gc-sections \
  -DARMCM3 \
  -D__CORTEX_M3 \
  -D__CMSIS_RTOS \
  -O0

all: $(SRC_C) $(SRC) boot.o
	$(CC) $^ $(CFLAGS) -T $(LINKER_SCRIPT) -o $(BINARY)
	$(OBJ) -D $(BINARY) > $(BINARY)_$(BINARY_OBJDUMP)

boot.o: $(SRC_ASM)
	$(CC) $(CFLAGS) -c $^ -o $@

# Ctrl-A, then X to quit QEMU
run: $(BINARY)
	-$(QEMU_RUN_COMMAND) 
	@echo $$? " has exited"

gdbserver: $(BINARY)
	$(QEMU_RUN_COMMAND) -S -s -d int,cpu_reset,guest_errors -D qemu_exceptions.log

help:
	$(QEMU_COMMAND) --machine help

gdb: $(BINARY)
	$(GDB) $(BINARY) -ex "target remote:1234" -nh -x ~/.gdbinit 

clean:
	rm -f *.o *.elf *.txt test_runner qemu_exceptions.log


# ---- Host test configuration ----
HOST_CC     ?= gcc
HOST_CFLAGS ?= -g3 -O0 -Wall -Wextra -Isrc/core -I$(TEST_DIR)

CORE_SRC    = $(wildcard src/core/*.c) -lm 
TEST_DIR    = tests/unit
TEST_SRC    = $(wildcard $(TEST_DIR)/*.c)
#MOCK_SRC   = $(TEST_DIR)/mock_port.c    # your stubs

# Compiles host unit test binary with debug symbols
test_runner: $(CORE_SRC) $(TEST_SRC)   
	$(HOST_CC) $(HOST_CFLAGS) $^ -o $@

# Runs test binary directly in terminal
core_tests: test_runner
	@./test_runner


# ---- RTOS Validation Test Configuration ----
RTOS_VALID_DIR  = tests/rtos_tests
RTOS_VALID_SRC  = $(wildcard $(RTOS_VALID_DIR)/*.c) \
                  $(wildcard $(RTOS_VALID_DIR)/Source/*.c)
RTOS_VALID_INC  = -I$(RTOS_VALID_DIR) \
                  -I$(RTOS_VALID_DIR)/Include \
                  -I$(RTOS_VALID_DIR)/Config

RTOS_CORE_SRC   = $(filter-out src/main.c, $(SRC))

RTOS_VALID_DEFS = -DRTE_Components_H -D__RTX -DUSE_RTX

RTOS_TEST_ELF = rtos_validation.elf

rtos_validation.elf: $(SRC_C) $(RTOS_CORE_SRC) $(RTOS_VALID_SRC) boot.o
	$(CC) $^ $(CFLAGS) $(RTOS_VALID_INC) $(RTOS_VALID_DEFS) \
	      -T $(LINKER_SCRIPT) -o $@
	$(OBJ) -D $@ > rtos_validation_objdump.txt
  
run-rtos-tests: rtos_validation.elf
	-$(QEMU_RUN_COMMAND) -device loader,file=$<