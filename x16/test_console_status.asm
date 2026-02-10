;
; Test probe: sample REG_CON_STATUS and print byte values as hex.
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

    mov si, prefix
    call tx_string

    mov cx, 16
.sample:
    mov al, [es:REG_CON_STATUS]
    call tx_byte_hex
    mov al, ' '
    mov [es:REG_TX_FIFO], al
    loop .sample

    mov al, 13
    mov [es:REG_TX_FIFO], al
    mov al, 10
    mov [es:REG_TX_FIFO], al

.halt:
    hlt
    jmp .halt

tx_string:
    lodsb
    test al, al
    jz .done
    mov [es:REG_TX_FIFO], al
    jmp tx_string
.done:
    ret

tx_byte_hex:
    push ax
    mov ah, al
    shr al, 4
    call tx_hex_nibble
    mov al, ah
    and al, 0Fh
    call tx_hex_nibble
    pop ax
    ret

tx_hex_nibble:
    cmp al, 9
    jbe .digit
    add al, 'A' - 10
    jmp .emit
.digit:
    add al, '0'
.emit:
    mov [es:REG_TX_FIFO], al
    ret

prefix db "test_console_status: REG_CON_STATUS samples ",0
