;
; Test probe: issue IN from port 0x60 to exercise I/O port exit path.
; Preferred IOPORT keeps module loadable on hosts without explicit support.
;

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX, MODULE_CAP_IOPORT

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov ax, MMIO_BASE shr 4
    mov es, ax

    mov si, prefix
.tx:
    lodsb
    test al, al
    jz .probe
    mov [es:REG_TX_FIFO], al
    jmp .tx

.probe:
    in al, 60h

    ; Reaching here means host provided I/O emulation.
    mov si, suffix
.tx2:
    lodsb
    test al, al
    jz .halt
    mov [es:REG_TX_FIFO], al
    jmp .tx2

.halt:
    hlt
    jmp .halt

prefix db "test_ioport_probe: issuing IN 60h",13,10,0
suffix db "test_ioport_probe: IN completed",13,10,0
