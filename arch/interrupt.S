.macro m_save_registers
    addi a1, a1, -60
    s32i a0,  a1, 0
    s32i a4,  a1, 4
    s32i a5,  a1, 8
    s32i a6,  a1, 12 
    s32i a7,  a1, 16
    s32i a8,  a1, 20
    s32i a9,  a1, 24
    s32i a10, a1, 28
    s32i a11, a1, 32
    s32i a12, a1, 36
    s32i a13, a1, 40
    s32i a14, a1, 44
    s32i a15, a1, 48
    rsr.epc1 a2
    s32i a2, a1, 52
    rsr.ps a2
    s32i a2, a1, 56
.endm

.macro m_restore_registers
    l32i a0,  a1, 0
    l32i a4,  a1, 4
    l32i a5,  a1, 8
    l32i a6,  a1, 12
    l32i a7,  a1, 16
    l32i a8,  a1, 20
    l32i a9,  a1, 24
    l32i a10, a1, 28
    l32i a11, a1, 32
    l32i a12, a1, 36
    l32i a13, a1, 40
    l32i a14, a1, 44
    l32i a15, a1, 48
    l32i a2,  a1, 52
    wsr.epc1 a2
    l32i a2,  a1, 56
    wsr.ps a2
    rsync
    addi a1,  a1, 60
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
            j Kernel_Kernel_Panic_NonMaskable 

        .org _etssos_interrupt_vector_base + 0x30
        .type KernelException, @function
        KernelException:
            j _etssos_kernel_interrupt_entry

        .org _etssos_interrupt_vector_base + 0x50
        .type UserException, @function
        UserException:
            j _etssos_user_interrupt_entry

        .org _etssos_interrupt_vector_base + 0x70
        .type DoubleException, @function
        DoubleException:
            j Kernel_Kernel_Panic_Double

        .org _etssos_interrupt_vector_base + 0x80
        .type Reset, @function
        Reset:
            j _etssos_reset
            _etssos_reset_cnt:
            j _etssos_boot_entry

.section .text
    .align 4
    .global _etssos_kernel_interrupt_entry
    .type _etssos_kernel_interrupt_entry, @function
    _etssos_kernel_interrupt_entry:
        m_save_registers
        movi a2, Kernel_Scheduler_Current
        l32i a2, a2, 0
        beqz a2, 1f
        s32i a1, a2, 0
        1:
        call0 Kernel_Kernel_Panic
        movi a2, Kernel_Scheduler_Switched
        l32i a3, a2, 0
        beqz a3, 2f
        movi a3, 0
        s32i a3, a2, 0
        movi a2, Kernel_Scheduler_Current
        l32i a2, a2, 0
        l32i a1, a2, 0
        2:
        m_restore_registers
        rfe

    .align 4
    .global _etssos_user_interrupt_entry
    .type _etssos_user_interrupt_entry, @function
    _etssos_user_interrupt_entry:
        m_save_registers
        movi a2, Kernel_Scheduler_Current
        l32i a2, a2, 0
        beqz a2, 1f
        s32i a1, a2, 0
        1:
        call0 Kernel_Kernel_Panic_UserError
        movi a2, Kernel_Scheduler_Switched
        l32i a3, a2, 0
        beqz a3, 2f
        movi a3, 0
        s32i a3, a2, 0
        movi a2, Kernel_Scheduler_Current
        l32i a2, a2, 0
        l32i a1, a2, 0
        2:
        m_restore_registers
        rfe

    .align 4
    .global Kernel_Scheduler_Start
    .type Kernel_Scheduler_Start, @function
    Kernel_Scheduler_Start:
        call0 Kernel_Scheduler_Tick
        movi a2, Kernel_Scheduler_Current
        l32i a2, a2, 0
        l32i a1, a2, 0
        l32i a0, a1, 0
        addi a1, a1, 60
        jx a0

    .type _etssos_reset, @function
    _etssos_reset:
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
        j _etssos_reset_cnt
