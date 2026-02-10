; Speed probe: fixed-count MMIO status reads.
; Read count: 200 * 2000 = 400,000 MMIO reads (exit-heavy path).
;

include 'module_impl.inc'
include 'module_flags.inc'
include 'bench.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX or MODULE_CAP_TIME_TICKS, 0

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov ax, MMIO_BASE shr 4
    mov es, ax

    BenchTelemetry_Init 00061A80h, 0
    BenchTelemetry_ReadStart

    xor dx, dx
    mov bx, 200

.outer:
    mov cx, 2000
.inner:
    mov al, [es:REG_CON_STATUS]
    xor dl, al
    dec cx
    jnz .inner
    dec bx
    jnz .outer

    BenchTelemetry_ReadEnd

.halt:
    hlt
    jmp .halt
