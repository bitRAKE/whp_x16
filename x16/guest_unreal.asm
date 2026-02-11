;
; Console-only test of unreal mode
;

include 'module_unreal_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 0, MODULE_CAP_MMIO_CONSOLE_TX or MODULE_CAP_UNREAL_SEGMENTS, 0

use16
org 0x2000

Start:
	; Uses host-provided flat data limits via module_unreal_impl.inc.
	mov esi, msg
	mov edi, MMIO_BASE + REG_TX_FIFO
tx:
	mov al, [esi]
	inc esi
	mov [edi], al
	test al, al
	jnz tx
halt:
	hlt
	jmp halt

rb 0x1_0000

msg db "guest_unreal: host-set segment limits ok",13,10,0
