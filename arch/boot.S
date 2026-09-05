.section .text
    .global _etssos_boot_entry
    .type _etssos_boot_entry, @function

    _etssos_boot_entry:
        # Stack Setup
        movi a1, __stack_top

        # Zero BSS
        movi a2, _bss_start
        movi a3, _bss_end
        _zero_bss:
            beq a2, a3, _bss_done
            s32i a0, a2, 0
            addi a2, a2, 4
        _bss_done:

        call0 kernel_main 

    __endless_loop:
        j __endless_loop
