#!/bin/bash

# 2. Run QEMU with semihosting (this links QEMU's I/O directly to your terminal)
qemu-system-arm -machine lm3s6965evb\
  -cpu cortex-m3 \
  -m 4096 \
  -nographic \
  -semihosting \
  --semihosting-config enable=on,target=native \
  -serial mon:stdio \
  -device loader,file=kernel.elf\
  -machine accel=tcg

