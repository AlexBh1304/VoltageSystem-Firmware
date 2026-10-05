CC= riscv-none-elf-gcc

INCDIR= ../ch32v003-peripheral-drivers/Inc/
SRCDIR= ../ch32v003-peripheral-drivers/Src/

CFLAGS= -c -g -march=rv32ec -mabi=ilp32e -nostdlib -Wall -O0 -I$(INCDIR)
LDFLAGS= -T linker.ld -nostdlib


all: firmware.elf

clean:
	rm -rf *.o *.elf

gpio.o: $(SRCDIR)gpio.c
	$(CC) $(CFLAGS) $^ -o $@

rcc.o: $(SRCDIR)rcc.c
	$(CC) $(CFLAGS) $^ -o $@

usart.o: $(SRCDIR)usart.c
	$(CC) $(CFLAGS) $^ -o $@

adc.o: $(SRCDIR)adc.c
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) $^ -o $@

startup.o: startup.s
	$(CC) $(CFLAGS) $^ -o $@

firmware.elf: main.o gpio.o rcc.o startup.o usart.o adc.o
	$(CC) $(LDFLAGS) $^ -o $@
load:
	wch-openocd -f wch-riscv.cfg
