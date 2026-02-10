;
; Test probe: fill 320x200 LFB with a simple gradient and present.
;

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_FRAMEBUFFER, MODULE_CAP_MMIO_CONSOLE_TX

use16
org 0x7C00

    xor ax, ax
    mov ds, ax

    mov bx, LFB_BASE shr 4
    mov bp, 4
    xor dx, dx

.segment_loop:
    push bx
    pop es
    xor di, di
    mov cx, 16000

.pixel_loop:
    mov al, dl
    stosb               ; B
    mov al, dh
    stosb               ; G
    mov al, dl
    xor al, dh
    stosb               ; R
    xor al, al
    stosb               ; A
    inc dl
    loop .pixel_loop

    add bx, 1000h
    add dh, 40h
    dec bp
    jnz .segment_loop

    mov ax, MMIO_BASE shr 4
    mov es, ax
    mov byte [es:REG_FB_PRESENT], 1

.halt:
    hlt
    jmp .halt
