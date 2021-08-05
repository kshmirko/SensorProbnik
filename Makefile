# Название: Makefile
# Автор: ph0en1x
# Копирайт: https://ph0en1x.net
# Лицензия: MIT

# Название проекта.
# Имя основного С-файла без расширения, пример для 'project1.c': 'project1'.
PROJECT = main

# Тип чипа для AVR GCC и частота ядра. 
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
GCC_MCU = atmega32a
CLOCK_HZ   = 16000000

# Опции для AVRDUDE.
# https://ph0en1x.net/77-avrdude-full-howto-samples-options-gui-linux.html
AVRDUDE_MCU             = m32a
AVRDUDE_PROGRAMMER      = usbasp
AVRDUDE_PROGRAMMER_PORT = usb

# Fuses
FUSE_L = 0xe1
FUSE_H = 0xd9
FUSE_E = 0xff

# Список дополнительных C-файлов для компиляции (указывать через пробел).
C_FILES = twi.c uart.c ssd1306.c font.c dht11.c 


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CFLAGS        = -Os -Wall -mcall-prologues -std=gnu99 -mmcu=$(GCC_MCU) -DF_CPU=$(CLOCK_HZ)UL 
FUSES         = -U lfuse:w:$(FUSE_L):m -U hfuse:w:$(FUSE_H):m -U efuse:w:$(FUSE_E):m
FLASH         = -U flash:w:$(PROJECT).hex

AVR_GCC       = /Users/kshmirko/.platformio/packages/toolchain-atmelavr/bin/avr-gcc
AVR_OBJCOPY   = /Users/kshmirko/.platformio/packages/toolchain-atmelavr/bin/avr-objcopy
AVR_SIZE      = /Users/kshmirko/.platformio/packages/toolchain-atmelavr/bin/avr-size
AVR_OBJDUMP   = /Users/kshmirko/.platformio/packages/toolchain-atmelavr/bin/avr-objdump
AVRDUDE       = /Users/kshmirko/.platformio/packages/toolchain-atmelavr/bin/avrdude
REMOVE        = `which rm`
VIMR          = `which vimr`
TAR           = `which tar`
DATETIME      = `date +"%d-%m-%Y"`

AVRDUDE_CMD   = $(AVRDUDE) -p $(AVRDUDE_MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PROGRAMMER_PORT) -v

%.elf: %.c
	$(AVR_GCC) $(CFLAGS) $< $(C_FILES) -o $@

%.hex: %.elf
	$(AVR_OBJCOPY) -R .eeprom -O ihex $< $@

all: clean elf hex

program: $(PROJECT).hex
	$(AVRDUDE_CMD) $(FLASH)

fuses:
	$(AVRDUDE_CMD) $(FUSES)

elf: $(PROJECT).elf

hex: $(PROJECT).hex

size: $(PROJECT).elf
	$(AVR_SIZE) -C --mcu=$(GCC_MCU) $(PROJECT).elf


disasm: $(PROJECT).elf
	$(AVR_OBJDUMP) -d $(PROJECT).elf

clean:
	$(REMOVE) -f *.hex *.elf *.o

edit:	
	$(VIMR) $(PROJECT).c

tar:
	$(TAR) -zcf $(PROJECT)_$(DATETIME).tgz ./* 

