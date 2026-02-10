
RAM_SIZE     = 2 * 1024 * 1024  ; 2 MiB
BOOT_ADDR    = 0x00007C00       ; physical address for guest code
LFB_BASE     = 0x000A0000       ; 320x200x32 fits in 256 KiB (A0000..E0000)
LFB_WIDTH    = 320
LFB_HEIGHT   = 200
LFB_BPP      = 4
MMIO_BASE    = 0x000E0000       ; 64 KiB MMIO window (E000:0000)
MMIO_SIZE    = 0x00010000

; MMIO registers

REG_TX_FIFO    = 0x0000 ; W: byte -> console
REG_CON_STATUS = 0x0004 ; R: bit0=tx ready
REG_FB_PRESENT = 0x0010 ; W: any -> present
REG_FB_GEOM    = 0x0014 ; R/W: (width<<16)|height
REG_KBD_POP    = 0x0020 ; R: 0 if none (not implemented here)
REG_TICKS_LO   = 0x0030 ; R: low 32 of GetTickCount64
REG_TICKS_HI   = 0x0034 ; R: high 32
REG_DOORBELL   = 0x00F0 ; W: 1=flush, 2=present
