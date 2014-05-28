# Makefile for the kernel module

# Set the module name
MODULE := proc/Mips

FILES := exception.c _syscall.c _proc.c

MIPSSRC += $(patsubst %, $(MODULE)/%, $(FILES))

