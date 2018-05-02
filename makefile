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
main: stm.c pwm.c twimaster.c ina219.c tmp101.c krnl.c main.c

%.hex: %
	$(OBJCOPY) -O ihex $< $@
