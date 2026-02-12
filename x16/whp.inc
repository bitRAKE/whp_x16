; WinHvPlatform
;
; Register and memory enums/structures excerpt from:
;	Windows Kits\10\Include\10.0.26100.0\um\WinHvPlatformDefs.h

; x64 General purpose registers
WHvX64RegisterRax	:= 0x00000000
WHvX64RegisterRcx	:= 0x00000001
WHvX64RegisterRdx	:= 0x00000002
WHvX64RegisterRbx	:= 0x00000003
WHvX64RegisterRsp	:= 0x00000004
WHvX64RegisterRbp	:= 0x00000005
WHvX64RegisterRsi	:= 0x00000006
WHvX64RegisterRdi	:= 0x00000007
WHvX64RegisterR8	:= 0x00000008
WHvX64RegisterR9	:= 0x00000009
WHvX64RegisterR10	:= 0x0000000A
WHvX64RegisterR11	:= 0x0000000B
WHvX64RegisterR12	:= 0x0000000C
WHvX64RegisterR13	:= 0x0000000D
WHvX64RegisterR14	:= 0x0000000E
WHvX64RegisterR15	:= 0x0000000F
WHvX64RegisterRip	:= 0x00000010
WHvX64RegisterRflags	:= 0x00000011

; x64 Segment registers
WHvX64RegisterEs	:= 0x00000012
WHvX64RegisterCs	:= 0x00000013
WHvX64RegisterSs	:= 0x00000014
WHvX64RegisterDs	:= 0x00000015
WHvX64RegisterFs	:= 0x00000016
WHvX64RegisterGs	:= 0x00000017
WHvX64RegisterLdtr	:= 0x00000018
WHvX64RegisterTr	:= 0x00000019

; x64 Table registers
WHvX64RegisterIdtr	:= 0x0000001A
WHvX64RegisterGdtr	:= 0x0000001B

; x64 Control Registers
WHvX64RegisterCr0	:= 0x0000001C
WHvX64RegisterCr2	:= 0x0000001D
WHvX64RegisterCr3	:= 0x0000001E
WHvX64RegisterCr4	:= 0x0000001F
WHvX64RegisterCr8	:= 0x00000020

; x64 Debug Registers
WHvX64RegisterDr0	:= 0x00000021
WHvX64RegisterDr1	:= 0x00000022
WHvX64RegisterDr2	:= 0x00000023
WHvX64RegisterDr3	:= 0x00000024
WHvX64RegisterDr6	:= 0x00000025
WHvX64RegisterDr7	:= 0x00000026

; x64 Extended Control Registers
WHvX64RegisterXCr0	:= 0x00000027

; x64 Virtual Control Registers
WHvX64RegisterVirtualCr0	:= 0x00000028
WHvX64RegisterVirtualCr3	:= 0x00000029
WHvX64RegisterVirtualCr4	:= 0x0000002A
WHvX64RegisterVirtualCr8	:= 0x0000002B

; x64 Floating Point and Vector Registers
WHvX64RegisterXmm0	:= 0x00001000
WHvX64RegisterXmm1	:= 0x00001001
WHvX64RegisterXmm2	:= 0x00001002
WHvX64RegisterXmm3	:= 0x00001003
WHvX64RegisterXmm4	:= 0x00001004
WHvX64RegisterXmm5	:= 0x00001005
WHvX64RegisterXmm6	:= 0x00001006
WHvX64RegisterXmm7	:= 0x00001007
WHvX64RegisterXmm8	:= 0x00001008
WHvX64RegisterXmm9	:= 0x00001009
WHvX64RegisterXmm10	:= 0x0000100A
WHvX64RegisterXmm11	:= 0x0000100B
WHvX64RegisterXmm12	:= 0x0000100C
WHvX64RegisterXmm13	:= 0x0000100D
WHvX64RegisterXmm14	:= 0x0000100E
WHvX64RegisterXmm15	:= 0x0000100F

WHvX64RegisterFpMmx0	:= 0x00001010
WHvX64RegisterFpMmx1	:= 0x00001011
WHvX64RegisterFpMmx2	:= 0x00001012
WHvX64RegisterFpMmx3	:= 0x00001013
WHvX64RegisterFpMmx4	:= 0x00001014
WHvX64RegisterFpMmx5	:= 0x00001015
WHvX64RegisterFpMmx6	:= 0x00001016
WHvX64RegisterFpMmx7	:= 0x00001017

WHvX64RegisterFpControlStatus	:= 0x00001018
WHvX64RegisterXmmControlStatus	:= 0x00001019

; x64 MSRs
WHvX64RegisterTsc		:= 0x00002000
WHvX64RegisterEfer		:= 0x00002001
WHvX64RegisterKernelGsBase	:= 0x00002002
WHvX64RegisterApicBase		:= 0x00002003
WHvX64RegisterPat		:= 0x00002004
WHvX64RegisterSysenterCs	:= 0x00002005
WHvX64RegisterSysenterEip	:= 0x00002006
WHvX64RegisterSysenterEsp	:= 0x00002007
WHvX64RegisterStar		:= 0x00002008
WHvX64RegisterLstar		:= 0x00002009
WHvX64RegisterCstar		:= 0x0000200A
WHvX64RegisterSfmask		:= 0x0000200B
WHvX64RegisterInitialApicId	:= 0x0000200C

WHvX64RegisterMsrMtrrCap	:= 0x0000200D
WHvX64RegisterMsrMtrrDefType	:= 0x0000200E

WHvX64RegisterMsrMtrrPhysBase0	:= 0x00002010
WHvX64RegisterMsrMtrrPhysBase1	:= 0x00002011
WHvX64RegisterMsrMtrrPhysBase2	:= 0x00002012
WHvX64RegisterMsrMtrrPhysBase3	:= 0x00002013
WHvX64RegisterMsrMtrrPhysBase4	:= 0x00002014
WHvX64RegisterMsrMtrrPhysBase5	:= 0x00002015
WHvX64RegisterMsrMtrrPhysBase6	:= 0x00002016
WHvX64RegisterMsrMtrrPhysBase7	:= 0x00002017
WHvX64RegisterMsrMtrrPhysBase8	:= 0x00002018
WHvX64RegisterMsrMtrrPhysBase9	:= 0x00002019
WHvX64RegisterMsrMtrrPhysBaseA	:= 0x0000201A
WHvX64RegisterMsrMtrrPhysBaseB	:= 0x0000201B
WHvX64RegisterMsrMtrrPhysBaseC	:= 0x0000201C
WHvX64RegisterMsrMtrrPhysBaseD	:= 0x0000201D
WHvX64RegisterMsrMtrrPhysBaseE	:= 0x0000201E
WHvX64RegisterMsrMtrrPhysBaseF	:= 0x0000201F

WHvX64RegisterMsrMtrrPhysMask0	:= 0x00002040
WHvX64RegisterMsrMtrrPhysMask1	:= 0x00002041
WHvX64RegisterMsrMtrrPhysMask2	:= 0x00002042
WHvX64RegisterMsrMtrrPhysMask3	:= 0x00002043
WHvX64RegisterMsrMtrrPhysMask4	:= 0x00002044
WHvX64RegisterMsrMtrrPhysMask5	:= 0x00002045
WHvX64RegisterMsrMtrrPhysMask6	:= 0x00002046
WHvX64RegisterMsrMtrrPhysMask7	:= 0x00002047
WHvX64RegisterMsrMtrrPhysMask8	:= 0x00002048
WHvX64RegisterMsrMtrrPhysMask9	:= 0x00002049
WHvX64RegisterMsrMtrrPhysMaskA	:= 0x0000204A
WHvX64RegisterMsrMtrrPhysMaskB	:= 0x0000204B
WHvX64RegisterMsrMtrrPhysMaskC	:= 0x0000204C
WHvX64RegisterMsrMtrrPhysMaskD	:= 0x0000204D
WHvX64RegisterMsrMtrrPhysMaskE	:= 0x0000204E
WHvX64RegisterMsrMtrrPhysMaskF	:= 0x0000204F

WHvX64RegisterMsrMtrrFix64k00000:= 0x00002070
WHvX64RegisterMsrMtrrFix16k80000:= 0x00002071
WHvX64RegisterMsrMtrrFix16kA0000:= 0x00002072
WHvX64RegisterMsrMtrrFix4kC0000	:= 0x00002073
WHvX64RegisterMsrMtrrFix4kC8000	:= 0x00002074
WHvX64RegisterMsrMtrrFix4kD0000	:= 0x00002075
WHvX64RegisterMsrMtrrFix4kD8000	:= 0x00002076
WHvX64RegisterMsrMtrrFix4kE0000	:= 0x00002077
WHvX64RegisterMsrMtrrFix4kE8000	:= 0x00002078
WHvX64RegisterMsrMtrrFix4kF0000	:= 0x00002079
WHvX64RegisterMsrMtrrFix4kF8000	:= 0x0000207A

WHvX64RegisterTscAux			:= 0x0000207B
WHvX64RegisterBndcfgs			:= 0x0000207C
WHvX64RegisterMCount			:= 0x0000207E
WHvX64RegisterACount			:= 0x0000207F
WHvX64RegisterSpecCtrl			:= 0x00002084
WHvX64RegisterPredCmd			:= 0x00002085
WHvX64RegisterTscVirtualOffset		:= 0x00002087
WHvX64RegisterTsxCtrl			:= 0x00002088
WHvX64RegisterXss			:= 0x0000208B
WHvX64RegisterUCet			:= 0x0000208C
WHvX64RegisterSCet			:= 0x0000208D
WHvX64RegisterSsp			:= 0x0000208E
WHvX64RegisterPl0Ssp			:= 0x0000208F
WHvX64RegisterPl1Ssp			:= 0x00002090
WHvX64RegisterPl2Ssp			:= 0x00002091
WHvX64RegisterPl3Ssp			:= 0x00002092
WHvX64RegisterInterruptSspTableAddr	:= 0x00002093
WHvX64RegisterTscDeadline		:= 0x00002095
WHvX64RegisterTscAdjust			:= 0x00002096
WHvX64RegisterUmwaitControl		:= 0x00002098
WHvX64RegisterXfd			:= 0x00002099
WHvX64RegisterXfdErr			:= 0x0000209A

; Feature control and nested capability MSRs
WHvX64RegisterMsrIa32MiscEnable		:= 0x000020A0
WHvX64RegisterIa32FeatureControl	:= 0x000020A1
WHvX64RegisterIa32VmxBasic		:= 0x000020A2
WHvX64RegisterIa32VmxPinbasedCtls	:= 0x000020A3
WHvX64RegisterIa32VmxProcbasedCtls	:= 0x000020A4
WHvX64RegisterIa32VmxExitCtls		:= 0x000020A5
WHvX64RegisterIa32VmxEntryCtls		:= 0x000020A6
WHvX64RegisterIa32VmxMisc		:= 0x000020A7
WHvX64RegisterIa32VmxCr0Fixed0		:= 0x000020A8
WHvX64RegisterIa32VmxCr0Fixed1		:= 0x000020A9
WHvX64RegisterIa32VmxCr4Fixed0		:= 0x000020AA
WHvX64RegisterIa32VmxCr4Fixed1		:= 0x000020AB
WHvX64RegisterIa32VmxVmcsEnum		:= 0x000020AC
WHvX64RegisterIa32VmxProcbasedCtls2	:= 0x000020AD
WHvX64RegisterIa32VmxEptVpidCap		:= 0x000020AE
WHvX64RegisterIa32VmxTruePinbasedCtls	:= 0x000020AF
WHvX64RegisterIa32VmxTrueProcbasedCtls	:= 0x000020B0
WHvX64RegisterIa32VmxTrueExitCtls	:= 0x000020B1
WHvX64RegisterIa32VmxTrueEntryCtls	:= 0x000020B2
WHvX64RegisterAmdVmHsavePa		:= 0x000020B3
WHvX64RegisterAmdVmCr			:= 0x000020B4

; APIC state
WHvX64RegisterApicId		:= 0x00003002
WHvX64RegisterApicVersion	:= 0x00003003

; X2APIC state
WHvX64RegisterApicTpr		:= 0x00003008
WHvX64RegisterApicPpr		:= 0x0000300A
WHvX64RegisterApicEoi		:= 0x0000300B
WHvX64RegisterApicLdr		:= 0x0000300D
WHvX64RegisterApicSpurious	:= 0x0000300F
WHvX64RegisterApicIsr0		:= 0x00003010
WHvX64RegisterApicIsr1		:= 0x00003011
WHvX64RegisterApicIsr2		:= 0x00003012
WHvX64RegisterApicIsr3		:= 0x00003013
WHvX64RegisterApicIsr4		:= 0x00003014
WHvX64RegisterApicIsr5		:= 0x00003015
WHvX64RegisterApicIsr6		:= 0x00003016
WHvX64RegisterApicIsr7		:= 0x00003017
WHvX64RegisterApicTmr0		:= 0x00003018
WHvX64RegisterApicTmr1		:= 0x00003019
WHvX64RegisterApicTmr2		:= 0x0000301A
WHvX64RegisterApicTmr3		:= 0x0000301B
WHvX64RegisterApicTmr4		:= 0x0000301C
WHvX64RegisterApicTmr5		:= 0x0000301D
WHvX64RegisterApicTmr6		:= 0x0000301E
WHvX64RegisterApicTmr7		:= 0x0000301F
WHvX64RegisterApicIrr0		:= 0x00003020
WHvX64RegisterApicIrr1		:= 0x00003021
WHvX64RegisterApicIrr2		:= 0x00003022
WHvX64RegisterApicIrr3		:= 0x00003023
WHvX64RegisterApicIrr4		:= 0x00003024
WHvX64RegisterApicIrr5		:= 0x00003025
WHvX64RegisterApicIrr6		:= 0x00003026
WHvX64RegisterApicIrr7		:= 0x00003027
WHvX64RegisterApicEse		:= 0x00003028
WHvX64RegisterApicIcr		:= 0x00003030
WHvX64RegisterApicLvtTimer	:= 0x00003032
WHvX64RegisterApicLvtThermal	:= 0x00003033
WHvX64RegisterApicLvtPerfmon	:= 0x00003034
WHvX64RegisterApicLvtLint0	:= 0x00003035
WHvX64RegisterApicLvtLint1	:= 0x00003036
WHvX64RegisterApicLvtError	:= 0x00003037
WHvX64RegisterApicInitCount	:= 0x00003038
WHvX64RegisterApicCurrentCount	:= 0x00003039
WHvX64RegisterApicDivide	:= 0x0000303E
WHvX64RegisterApicSelfIpi	:= 0x0000303F

; Synic registers
WHvRegisterSint0	:= 0x00004000
WHvRegisterSint1	:= 0x00004001
WHvRegisterSint2	:= 0x00004002
WHvRegisterSint3	:= 0x00004003
WHvRegisterSint4	:= 0x00004004
WHvRegisterSint5	:= 0x00004005
WHvRegisterSint6	:= 0x00004006
WHvRegisterSint7	:= 0x00004007
WHvRegisterSint8	:= 0x00004008
WHvRegisterSint9	:= 0x00004009
WHvRegisterSint10	:= 0x0000400A
WHvRegisterSint11	:= 0x0000400B
WHvRegisterSint12	:= 0x0000400C
WHvRegisterSint13	:= 0x0000400D
WHvRegisterSint14	:= 0x0000400E
WHvRegisterSint15	:= 0x0000400F
WHvRegisterScontrol	:= 0x00004010
WHvRegisterSversion	:= 0x00004011
WHvRegisterSiefp	:= 0x00004012
WHvRegisterSimp		:= 0x00004013
WHvRegisterEom		:= 0x00004014

; Hypervisor defined registers
WHvRegisterVpRuntime		:= 0x00005000
WHvX64RegisterHypercall		:= 0x00005001
WHvRegisterGuestOsId		:= 0x00005002
WHvRegisterVpAssistPage		:= 0x00005013
WHvRegisterReferenceTsc		:= 0x00005017
WHvRegisterReferenceTscSequence	:= 0x0000501A
WHvX64RegisterNestedGuestState	:= 0x00005050
WHvX64RegisterNestedCurrentVmGpa:= 0x00005051
WHvX64RegisterNestedVmxInvEpt	:= 0x00005052
WHvX64RegisterNestedVmxInvVpid	:= 0x00005053

; Interrupt / Event Registers
WHvRegisterPendingInterruption			:= 0x80000000
WHvRegisterInterruptState			:= 0x80000001
WHvRegisterPendingEvent				:= 0x80000002
WHvRegisterPendingEvent1			:= 0x80000003
WHvX64RegisterDeliverabilityNotifications	:= 0x80000004
WHvRegisterDeliverabilityNotifications		:= 0x80000004
WHvRegisterInternalActivityState		:= 0x80000005
WHvX64RegisterPendingDebugException		:= 0x80000006
WHvRegisterPendingEvent2			:= 0x80000007
WHvRegisterPendingEvent3			:= 0x80000008

struct WHV_X64_SEGMENT_REGISTER
	Base		dq ?
	Limit		dd ?
	Selector	dw ?
	Attributes	dw ?
;		SegmentType		:4
;		NonSystemSegment	:1
;		DescriptorPrivilegeLevel:2
;		Present			:1
;		Reserved		:4
;		Available		:1
;		Long			:1
;		Default			:1
;		Granularity		:1
ends

WHvMapGpaRangeFlagRead    = 0x00000001
WHvMapGpaRangeFlagWrite   = 0x00000002
WHvMapGpaRangeFlagExecute = 0x00000004
