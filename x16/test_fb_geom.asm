;
; Test probe: read/write REG_FB_GEOM and print geometry mask.
;

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX or MODULE_CAP_MMIO_FRAMEBUFFER, 0

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov ax, MMIO_BASE shr 4
    mov es, ax

    mov si, prefix
    call tx_string

    mov bx, [es:REG_FB_GEOM]
    mov cx, [es:REG_FB_GEOM + 2]
    mov dx, cx
    mov ax, bx
    call tx_dword_hex

    ; Write back unchanged geometry.
    mov [es:REG_FB_GEOM], bx
    mov [es:REG_FB_GEOM + 2], cx
    mov byte [es:REG_FB_PRESENT], 1

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

prefix db "test_fb_geom: REG_FB_GEOM=0x",0
