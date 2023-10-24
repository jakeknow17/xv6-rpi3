K=kernel
U=user

TOOLPREFIX=aarch64-none-elf-

SRCS = \
	$K/start.o

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
CFLAGS += -MD
CFLAGS += -ffreestanding -fno-common -nostdinc -nostdlib -nostartfiles
CFLAGS += -I.
CFLAGS += -fno-stack-protector # May need to conditionally add this

LDFLAGS = -z max-page-size=4096

all: clean kernel8.img
	
$K/entry.o: $K/entry.S
	 $(TOOLPREFIX)as -c $K/entry.S -o $K/entry.o

$K/%.o: $K/%.c
	$(TOOLPREFIX)gcc $(CFLAGS) -c $< -o $@

kernel8.img: $K/entry.o $(OBJS)
	$(TOOLPREFIX)ld -m aarch64elf -nostdlib $K/entry.o $(OBJS) -T $K/kernel.ld -o kernel8.elf
	$(TOOLPREFIX)objcopy -O binary kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf kernel8.img $K/*.o $K/*.d  >/dev/null 2>/dev/null

qemu: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio