;
; Tick service guest
; Reads REG_TICKS_LO and prints eight hex digits.
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

	mov si, prefix
.tx_prefix:
	lodsb
	test al, al
	jz .print_ticks
	mov [es:REG_TX_FIFO], al
	jmp .tx_prefix

.print_ticks:
	mov ax, [es:REG_TICKS_LO + 2]
	call print_word_hex
	mov ax, [es:REG_TICKS_LO]
	call print_word_hex

	mov al, 13
	mov [es:REG_TX_FIFO], al
	mov al, 10
	mov [es:REG_TX_FIFO], al

.halt:
	hlt
	jmp .halt

print_word_hex:
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

prefix db "guest_ticks: ticks_lo=0x",0
