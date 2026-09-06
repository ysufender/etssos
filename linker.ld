MEMORY {
    dport0_seg : org = 0x3FF00000,      len = 0x10
    dram_seg   : org = 0x3FFE8000,      len = 0x18000 - 0x400
    iram_seg   : org = 0x40100000,      len = 0x8000
}

__stack_top = ORIGIN(dram_seg) + LENGTH(dram_seg);
ENTRY(_etssos_boot_entry);

SECTIONS {

    .bss (NOLOAD) : {
        _bss_start = ABSOLUTE(.);
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = ABSOLUTE(.);
    } >dram_seg

    .data : {
        _data_start = ABSOLUTE(.);
        *(.data*)
        . = ALIGN(4);
        _data_end = ABSOLUTE(.);
    } >dram_seg

    .text : {
        _text_start = ABSOLUTE(.);
        . = ALIGN(16);
        KEEP(*boot.o(.text.interrupt_vector))
        *boot.o(.literal*)
        *boot.o(.text*)
        *(.literal*)
        *(.text*)
        _text_end = ABSOLUTE(.);
    } > iram_seg

    .rodata : {
        _rodata_lma = LOADADDR(.rodata);
        _rodata_start = ABSOLUTE(.);
        *(.rodata*)
        . = ALIGN(4);
        _rodata_end = ABSOLUTE(.);
    } >dram_seg AT>iram_seg
}
