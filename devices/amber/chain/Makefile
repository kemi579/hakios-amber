CROSS ?= aarch64-linux-gnu-
CC     = $(CROSS)gcc
OBJCOPY= $(CROSS)objcopy

CFLAGS = -ffreestanding -nostdlib -fno-stack-protector -fno-pic -fno-pie \
         -march=armv8-a -O2 -Wall -Wextra

all: chain.bin

chain.elf: start.S
	$(CC) $(CFLAGS) -Ttext=0x40080000 -o $@ $^

chain.bin: chain.elf
	$(OBJCOPY) -O binary $< $@
	@echo "Built $@ ($(shell wc -c < $@) bytes)"

clean:
	rm -f chain.elf chain.bin

.PHONY: all clean
