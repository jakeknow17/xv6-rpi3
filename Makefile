K=kernel
U=user

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
	 aarch64-linux-gnu-gcc $(CFLAGS) -c $K/entry.S -o $K/entry.o

$K/%.0: $K/%.c
	aarch64-linux-gnu-gcc $(CFLAGS) -c $K/$< -o $K/$@

kernel8.img: $K/entry.o $(OBJS)
	aarch64-linux-gnu-ld -nostdlib $K/entry.o $(OBJS) -T $K/kernel.ld -o kernel8.elf
	aarch64-linux-gnu-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf $K/*.o $K/*.d  >/dev/null 2>/dev/null

qemu:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio