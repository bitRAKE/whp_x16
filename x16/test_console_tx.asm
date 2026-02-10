;
; Test probe: MMIO console TX using REG_CON_STATUS ready handshake.
;

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
.tx_next:
    lodsb
    test al, al
    jz .done

.wait_ready:
    mov dl, [es:REG_CON_STATUS]
    test dl, 1
    jz .wait_ready

    mov [es:REG_TX_FIFO], al
    jmp .tx_next

.done:
    mov al, 13
    mov [es:REG_TX_FIFO], al
    mov al, 10
    mov [es:REG_TX_FIFO], al

.halt:
    hlt
    jmp .halt

msg db "test_console_tx: status-gated console output",0
