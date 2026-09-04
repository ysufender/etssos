.section .data


.section .bss

.section .text
    .global _etssos_boot_entry
    .type _etssos_boot_entry, @function

    _etssos_boot_entry:
        j _etssos_boot_entry
