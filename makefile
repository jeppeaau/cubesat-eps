#########################################################
#          Simple makefile for avr development          #
#########################################################


#MCU name 
MCU     = atmega328p  
#MCU Frequency
F_CPU   = 16000000

#Compiler and flags
CC      = avr-gcc
CFLAGS  = -O2 -Wall -std=gnu11 -mmcu=$(MCU)
CPPFLAGS  = -DF_CPU=$(F_CPU)L

OBJCOPY = avr-objcopy

.PHONY: default
default: main.hex main
main: pwm.c twimaster.c ina219.c krnl.c main.c

%.hex: %
	$(OBJCOPY) -O ihex $< $@

#avr-dude command
########### avrdude -p m328p -P /dev/cu.usbmodemFD121 -c arduino -b 115200 -F -u -U flash:w:blink.hex
#change MCU "m328p", port "/dev/cu.usbmodemFD121", bautrate "115200",