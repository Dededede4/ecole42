#!/bin/bash
nasm -f elf64 -o virus.o virus.s
objcopy --dump-section .text=virus.bin virus.o
