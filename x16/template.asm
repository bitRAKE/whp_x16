; WHP16 template module
; - MMIO console output baseline
; - HLT return to host

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX, 0

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov ax, MMIO_BASE shr 4
    mov es, ax

    mov si, msg
.tx:
    lodsb
    test al, al
    jz .halt
    mov [es:REG_TX_FIFO], al
    jmp .tx

.halt:
    hlt
    jmp .halt

msg db "template: hello from x86-16",13,10,0
