;
; Test probe: unreal-segment path writing LFB via flat offsets.
;

include 'module_unreal_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_FRAMEBUFFER or MODULE_CAP_UNREAL_SEGMENTS, MODULE_CAP_MMIO_CONSOLE_TX

use16
org 0x2000

    mov edi, LFB_BASE
    mov cx, LFB_WIDTH * LFB_HEIGHT
    xor bl, bl

.fill:
    mov [edi], bl
    mov al, bl
    not al
    mov [edi + 1], al
    mov al, bl
    shl al, 1
    mov [edi + 2], al
    mov byte [edi + 3], 0
    add edi, 4
    inc bl
    dec cx
    jnz .fill

    mov edi, MMIO_BASE + REG_FB_PRESENT
    mov byte [edi], 1

.halt:
    hlt
    jmp .halt
