; Speed probe: fixed-count ALU loop for rough Mops/s baseline.
; Core-op count: 1000 * 20000 * 3 = 60,000,000 ALU ops.
;

include 'module_impl.inc'
include 'module_flags.inc'
include 'bench.inc'

Set_Module_Flags_V0 0, MODULE_CAP_TIME_TICKS, 0

use16
org 0x7C00

    xor ax, ax
    mov ds, ax
    mov ax, MMIO_BASE shr 4
    mov es, ax

    BenchTelemetry_Init 03938700h, 0
    BenchTelemetry_ReadStart

    mov ax, 0ACE1h
    mov dx, 01234h
    mov bx, 1000

.outer:
    mov cx, 20000
.inner:
    add ax, dx
    xor dx, ax
    rol ax, 1
    dec cx
    jnz .inner
    dec bx
    jnz .outer

    BenchTelemetry_ReadEnd

.halt:
    hlt
    jmp .halt
