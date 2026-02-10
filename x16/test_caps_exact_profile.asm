;
; Test probe: exact-profile policy negotiation failure path.
;

include 'module_impl.inc'
include 'module_flags.inc'

Set_Module_Flags_V0 MODULE_CAPS_POLICY_EXACT_PROFILE, MODULE_CAP_MMIO_CONSOLE_TX, 0

use16
org 0x7C00

.halt:
    hlt
    jmp .halt
