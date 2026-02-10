;
; Test probe: intentionally reload DS to trigger unreal-segment guard warning.
;

include 'module_unreal_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX or MODULE_CAP_UNREAL_SEGMENTS, 0

use16
org 0x2000

    ; Intentional: dropping DS back to real-mode cached limit should trigger
    ; runtime unreal segment guard warning.
    xor ax, ax
    mov ds, ax

    mov si, msg
    mov edi, MMIO_BASE + REG_TX_FIFO

.tx:
    lodsb
    test al, al
    jz .halt
    mov [es:edi], al
    jmp .tx

.halt:
    hlt
    jmp .halt

msg db "test_unreal_reset_ds: DS reloaded intentionally",13,10,0
