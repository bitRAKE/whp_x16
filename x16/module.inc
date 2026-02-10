;
; abstract external machine state
;	- memory regions
;	- register values
;	- emulation depenencies
;

MAX_MODULE_REG_COUNT = 64
MODULE_MAGIC = 'W16MOD00'

struct MODULE_HEADER
	magic	dq ?
	base	dd ?	; 32-bit address
	limit	dd ?	; address space needed from base
	regs	db ?	; registers [0-64]
	flags	rb 11	; emulation feature flags/capabilities
	codes	dd ?	; instruction/data bytes

; array of WHvX64Register* dword values from enum WHV_REGISTER_NAME
; array of ddq register values, WHV_REGISTER_VALUE

; code bytes

ends

define CommonRegister CommonRegister
iterate base,ax,cx,dx,bx,sp,bp,si,di,ip,flags
	CommonRegister.base? equ WHvX64RegisterR#base
	CommonRegister.e#base? equ WHvX64RegisterR#base
	CommonRegister.r#base? equ WHvX64RegisterR#base
end iterate
repeat 8,base:8
	CommonRegister.r#base? equ WHvX64RegisterR#base
end repeat
iterate base,Es,Cs,Ss,Ds,Fs,Gs
	CommonRegister.base? equ WHvX64Register#base
end iterate

calminstruction CommonToWHvX64Register dest*,src*
	transform src,CommonRegister
	compute src,src
	publish dest,src
end calminstruction

macro Create_Module_Registers line&
	iterate <name,value>,line

		; array of dword names from common register names
		CommonToWHvX64Register .%.reg, name
		dd .%.reg

		if % = %%
			; output register values
			repeat %%
				indx %
				align 16 ; required by WHV_REGISTER_VALUE
				value ; flexible definitions
			end repeat
			align 16 ; required by WHV_REGISTER_VALUE
			store %%:1 at header:MODULE_HEADER.regs
		end if
	end iterate
end macro
