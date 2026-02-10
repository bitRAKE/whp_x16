;
; module header flags/capabilities (v0 layout)
;

MODULE_CAPS_VERSION_LEGACY = 0
MODULE_CAPS_VERSION_V0 = 1

MODULE_CAPS_POLICY_STRICT_PREFERRED = 1 shl 0
MODULE_CAPS_POLICY_EXACT_PROFILE = 1 shl 1

MODULE_CAP_MMIO_CONSOLE_TX = 1 shl 0
MODULE_CAP_MMIO_FRAMEBUFFER = 1 shl 1
MODULE_CAP_MMIO_KEYBOARD = 1 shl 2
MODULE_CAP_MMIO_MOUSE = 1 shl 3
MODULE_CAP_IOPORT = 1 shl 4
MODULE_CAP_INT_DISPATCH = 1 shl 5
MODULE_CAP_BIOS_SUBSET = 1 shl 6
MODULE_CAP_DOS_SUBSET = 1 shl 7
MODULE_CAP_TIME_TICKS = 1 shl 8
MODULE_CAP_DEBUG_TRAPS = 1 shl 9
MODULE_CAP_UNREAL_SEGMENTS = 1 shl 10

macro Set_Module_Flags_V0 policy, required, preferred
	postpone
		store MODULE_CAPS_VERSION_V0:1 at header:MODULE_HEADER.flags + 0
		store policy:1 at header:MODULE_HEADER.flags + 1
		store required:4 at header:MODULE_HEADER.flags + 2
		store preferred:4 at header:MODULE_HEADER.flags + 6
		store 0:1 at header:MODULE_HEADER.flags + 10
	end postpone
end macro
