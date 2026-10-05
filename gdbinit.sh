#!/usr/bin/bash

riscv-none-elf-gdb firmware.elf \
    -ex "target remote localhost:3333" \
    -ex "monitor reset halt"\
    -ex "monitor flash write_image erase firmware.elf"\
    -ex "monitor reset halt"
