.section .text.interrupt_vector
    .global _etssos_interrupt_vector_base
    _etssos_interrupt_vector_base:
        .org _etssos_interrupt_vector_base + 0x10
        .type DebugException, @function
        DebugException:
            j Kernel_Panic_Debug

        .org _etssos_interrupt_vector_base + 0x20
        .type NMIException, @function
        NMIException:
            j NMIException 

        .org _etssos_interrupt_vector_base  + 0x30
        .type KernelException, @function
        KernelException:
            j Kernel_Panic

        .org _etssos_interrupt_vector_base  + 0x50
        .type UserException, @function
        UserException:
            j Kernel_Panic

        .org _etssos_interrupt_vector_base  + 0x70
        .type DoubleException, @function
        DoubleException:
            j Kernel_Panic

        .org _etssos_interrupt_vector_base  + 0x80
        .type Reset, @function
        Reset:
            call0 _etssos_reset
            j _etssos_boot_entry

.section .text
    .type _etssos_reset, @function
    _etssos_reset:
        movi a1, 0
        movi a2, 0
        movi a3, 0
        movi a4, 0
        movi a5, 0
        movi a6, 0
        movi a7, 0
        movi a8, 0
        movi a9, 0
        movi a10, 0
        movi a11, 0
        movi a12, 0
        movi a13, 0
        movi a14, 0
        movi a15, 0
        ret.n

    .global _etssos_interrupt_enable
    .type _etssos_interrupt_enable, @function
    _etssos_interrupt_enable:
        movi a2, 0x00000000
        wsr a2, PS
        rsync
        ret.n

    .global _etssos_interrupt_disable
    .type _etssos_interrupt_disable, @function
    _etssos_interrupt_disable:
        rsil a2, 15
        ret.n
