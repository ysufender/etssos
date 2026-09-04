.section .text
    .global _etssos_boot_entry
    .type _etssos_boot_entry, @function

    _etssos_boot_entry:
        # Stack Setup
        movi a1, __stack_top

        call0 kernel_main 

    __endless_loop:
        j __endless_loop
