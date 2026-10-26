CROSS ?= aarch64-none-elf-
CC    = $(CROSS)gcc
LD    = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -ffreestanding -fno-builtin -fno-stack-protector \
         -mgeneral-regs-only -mlittle-endian -mcpu=cortex-a78 \
         -O2 -Wall -Wextra
LDFLAGS = -T link.ld -nostdlib

OBJS = bootshim.o uart.o gic.o memmap.o efi_services.o

all: bootshim.bin

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

bootshim.elf: $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

bootshim.bin: bootshim.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.o *.elf *.bin

.PHONY: all clean
