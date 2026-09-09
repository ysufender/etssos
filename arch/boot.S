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

        # Copy rodata
        movi a2, _rodata_start
        movi a3, _rodata_end
        movi a4, _rodata_lma
        _copy_rodata:
            beq  a2, a3, _copy_done
            l32i a5, a4, 0
            s32i a5, a2, 0
            addi a2, a2, 4
            addi a4, a4, 4
            j    _copy_rodata
        _copy_done:

        j Kernel_Kernel_Main 
