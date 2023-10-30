K=kernel
U=user

TOOLPREFIX=aarch64-none-elf-

C_SRCS = \
	$K/start.c \
	$K/uart.c \
	$K/mailbox.c \
	$K/delay.c \
	$K/sd.c \

ASM_SRCS = \
	$K/entry.S \

C_OBJS = $(C_SRCS:.c=.o)
ASM_OBJS = $(ASM_SRCS:.S=.o)

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2
CFLAGS += -MD
CFLAGS += -ffreestanding -fno-common -nostdinc -nostdlib -nostartfiles
CFLAGS += -I. -I kernel/include
CFLAGS += -fno-stack-protector # May need to conditionally add this

LDFLAGS = -z max-page-size=4096

all: clean kernel8.img
	
$K/%.o: $K/%.S
	$(TOOLPREFIX)gcc $(CFLAGS) -c $< -o $@

$K/%.o: $K/%.c
	$(TOOLPREFIX)gcc $(CFLAGS) -c $< -o $@

kernel8.img: $(ASM_OBJS) $(C_OBJS)
	$(TOOLPREFIX)ld -m aarch64elf -nostdlib $(ASM_OBJS) $(C_OBJS) -T $K/kernel.ld -o kernel8.elf
	$(TOOLPREFIX)objcopy -O binary kernel8.elf kernel8.img

clean:
	rm -f kernel8.elf kernel8.img test.dd $K/*.o $K/*.d  >/dev/null 2>/dev/null

test.dd:
	dd if=/dev/zero of=test.dd bs=1M count=1024
	mformat -i test.dd -F

QEMU_OPTS = -M raspi3b -kernel kernel8.img -drive file=test.dd,if=sd,format=raw -nographic

qemu: kernel8.img test.dd
	qemu-system-aarch64 $(QEMU_OPTS)

qemu-gdb: kernel8.img test.dd
	qemu-system-aarch64 -s -S $(QEMU_OPTS)