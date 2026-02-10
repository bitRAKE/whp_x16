
; common helper to instantiate module composed of following section

include 'macro\struct.inc'
include 'whp.inc'
include 'module.inc'
include 'mmio.inc'

header::

MODULE_HEADER magic: MODULE_MAGIC

; Some common legacy start-up register values,
; see: https://www.fysnet.net/yourhelp.htm

Create_Module_Registers\
	cs,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,009Bh>,\
	ds,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,0093h>,\
	es,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,0093h>,\
	ss,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,0093h>,\
	fs,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,0093h>,\
	gs,	<WHV_X64_SEGMENT_REGISTER 0,0FFFFh,0,0093h>,\
	ip,	ddq MODULE_BASE,\
	flags,	ddq 2,\
	sp,	ddq 0xFFFE,\
	bp,	ddq 0x0882,\
	di,	ddq 0xFFFE,\
	si,	ddq 0x0100,\
	cx,	ddq 0x00FF,\
	bx,	ddq 0,\
	ax,	ddq 0

; Wait to get ORG and sizes of the following code section:
postpone
	MODULE_BASE := $$
	; Note: reserve bytes increase length, but not file size.
	length = $ - MODULE_BASE	; total expected bytes
	bytes = $@ - MODULE_BASE	; initialized size

	iterate <member,value>,\
		base,	MODULE_BASE,\
		limit, 	length,\
		codes,	bytes

		location equ MODULE_HEADER.member
		store value:sizeof location at header:location
	end iterate
end postpone
