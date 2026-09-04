MEMORY {
    dport0_seg : org = 0x3FF00000,      len = 0x10
    dram_seg   : org = 0x3FFE8000,      len = 0x18000 - 0x400
    iram_seg   : org = 0x40100000,      len = 0x8000
}

__stack_top = ORIGIN(dram_seg) + LENGTH(dram_seg);
ENTRY(_etssos_boot_entry);

SECTIONS {
    .rodata : {
        _rodata_start = ABSOLUTE(.);
        *(.rodata*)
        _rodata_end = ABSOLUTE(.);
    } >dram_seg

    .bss (NOLOAD) : {
        _bss_start = ABSOLUTE(.);
        *(.bss*)
        *(COMMON)
        _bss_end = ABSOLUTE(.);
    } >dram_seg

    .data : {
        _data_start = ABSOLUTE(.);
        *(.data*)
        _data_end = ABSOLUTE(.);
    } >dram_seg

    .literal : {
        _literal_start = ABSOLUTE(.);
        *(.literal*)
        _literal_end = ABSOLUTE(.);
    } > iram_seg

    .text : {
        _text_start = ABSOLUTE(.);
        *(.text*)
        _text_end = ABSOLUTE(.);
    } > iram_seg
}
