;
; Test probe: print REG_TICKS_HI and REG_TICKS_LO as 16 hex digits each.
;

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX or MODULE_CAP_TIME_TICKS, 0

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov ax, MMIO_BASE shr 4
    mov es, ax

    mov si, prefix_hi
    call tx_string
    mov bx, [es:REG_TICKS_HI]
    mov cx, [es:REG_TICKS_HI + 2]
    mov dx, cx
    mov ax, bx
    call tx_dword_hex

    mov si, prefix_lo
    call tx_string
    mov bx, [es:REG_TICKS_LO]
    mov cx, [es:REG_TICKS_LO + 2]
    mov dx, cx
    mov ax, bx
    call tx_dword_hex

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

tx_dword_hex:
    push ax
    mov ax, dx
    call tx_word_hex
    pop ax
    call tx_word_hex
    ret

tx_word_hex:
    push ax
    push cx
    push dx
    mov cx, 4
.nibble:
    rol ax, 4
    mov dl, al
    and dl, 0Fh
    cmp dl, 9
    jbe .digit
    add dl, 'A' - 10
    jmp .emit
.digit:
    add dl, '0'
.emit:
    mov [es:REG_TX_FIFO], dl
    loop .nibble
    pop dx
    pop cx
    pop ax
    ret

prefix_hi db "test_ticks_64: ticks_hi=0x",0
prefix_lo db " ticks_lo=0x",0
