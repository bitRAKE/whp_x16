; Speed probe: fixed-count RAM read/modify/write loop.
; Core-op count: 1000 * 20000 * 4 = 80,000,000 memory/ALU ops.
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

    BenchTelemetry_Init 04C4B400h, 0
    BenchTelemetry_ReadStart

    xor bx, bx
    mov dx, 1000

.outer:
    mov cx, 20000
.inner:
    mov al, [buffer + bx]
    add al, 1
    mov [buffer + bx], al
    inc bl
    dec cx
    jnz .inner
    dec dx
    jnz .outer

    BenchTelemetry_ReadEnd

.halt:
    hlt
    jmp .halt

buffer db 256 dup(0)
