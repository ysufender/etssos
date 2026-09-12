.include "arch/interrupt.S"

.section .text
    .global _etssos_boot_entry
    .type _etssos_boot_entry, @function
    _etssos_boot_entry:
        movi a2, _etssos_interrupt_vector_base
        wsr.vecbase a2
        rsync

        # Stack Setup
        movi a1, __stack_top

        # Zero BSS
        movi a2, _bss_start
        movi a3, _bss_end
        movi a4, 0
        _zero_bss:
            beq a2, a3, _bss_done
            s32i a4, a2, 0
            addi a2, a2, 4
            j _zero_bss
        _bss_done:

        j Kernel_Kernel_Main 
