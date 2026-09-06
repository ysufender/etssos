.macro SAVE_REGS
    addi a1,  a1, -64
    s32i a0,  a1, 0
    s32i a2,  a1, 8
    s32i a3,  a1, 12
    s32i a4,  a1, 16
    s32i a5,  a1, 20
    s32i a6,  a1, 24
    s32i a7,  a1, 28
    s32i a8,  a1, 32
    s32i a9,  a1, 36
    s32i a10, a1, 40
    s32i a11, a1, 44
    s32i a12, a1, 48
    s32i a13, a1, 52
    s32i a14, a1, 56
    s32i a15, a1, 60
.endm

.macro RESTORE_REGS
    l32i a0,  a1, 0
    l32i a2,  a1, 8
    l32i a3,  a1, 12
    l32i a4,  a1, 16
    l32i a5,  a1, 20
    l32i a6,  a1, 24
    l32i a7,  a1, 28
    l32i a8,  a1, 32
    l32i a9,  a1, 36
    l32i a10, a1, 40
    l32i a11, a1, 44
    l32i a12, a1, 48
    l32i a13, a1, 52
    l32i a14, a1, 56
    l32i a15, a1, 60
    addi a1,  a1, 64
.endm

.section .text.interrupt_vector
    .global _etssos_interrupt_vector_base
    _etssos_interrupt_vector_base:

        .org _etssos_interrupt_vector_base + 0x10
        .type DebugException, @function
        DebugException:
            j Kernel_Kernel_Panic_Debug

        .org _etssos_interrupt_vector_base + 0x20
        .type NMIException, @function
        NMIException:
            call0 Kernel_Kernel_Panic_NonMaskable 

        .org _etssos_interrupt_vector_base  + 0x30
        .type KernelException, @function
        KernelException:
            j _etssos_interrupt_kernel

        .org _etssos_interrupt_vector_base  + 0x50
        .type UserException, @function
        UserException:
            j Kernel_Kernel_Panic_UserError

        .org _etssos_interrupt_vector_base  + 0x70
        .type DoubleException, @function
        DoubleException:
            j Kernel_Kernel_Panic_Double

        .org _etssos_interrupt_vector_base  + 0x80
        .type Reset, @function
        Reset:
            call0 _etssos_reset
            j _etssos_boot_entry

.section .text
    .align 4
    .type _etssos_interrupt_kernel, @function
    _etssos_interrupt_kernel:
        SAVE_REGS
        j Kernel_Kernel_Panic
        RESTORE_REGS
        rfe

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

    .align 4
    .global _etssos_interrupt_enable
    .type _etssos_interrupt_enable, @function
    _etssos_interrupt_enable:
        movi a2, 0x00000000
        wsr a2, PS
        rsync
        ret.n

    .align 4
    .global _etssos_interrupt_disable
    .type _etssos_interrupt_disable, @function
    _etssos_interrupt_disable:
        rsil a2, 15
        ret.n
