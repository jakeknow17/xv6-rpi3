SECTIONS
{
    . = 0x80000;
    .text : {
        KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*)
        . = ALIGN(0x1000);
        _trampoline = .;
        *(trampsec)
        . = ALIGN(0x1000);
        ASSERT(. - _trampoline == 0x1000, "error: trampoline larger than one page");
        PROVIDE(etext = .);
        }

    .rodata : {
        . = ALIGN(16);
        *(.rodata .rodata.* .gnu.linkonce.r*)
    }

    .data : {
        . = ALIGN(16);
        *(.data .data.* .gnu.linkonce.d*)
    }

    .bss : {
        . = ALIGN(16);
        *(.bss .bss.*)
        *(COMMON)
    }
    _end = .;

    PROVIDE(end = .);
}