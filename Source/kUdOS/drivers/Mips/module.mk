# Makefile for the drivers module

# Set the module name
MODULE := drivers/Mips

FILES := _timer.S disk.c metadev.c polltty.c tty.c device.c drivers.c

MIPSSRC += $(patsubst %, $(MODULE)/%, $(FILES))
