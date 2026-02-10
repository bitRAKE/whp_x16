; WinHvPlatform




; WHP capability/property codes.
WHvCapabilityCodeHypervisorPresent                 = 0x00000000
WHvCapabilityCodeFeatures                          = 0x00000001
WHvCapabilityCodeExtendedVmExits                   = 0x00000002
WHvCapabilityCodeExceptionExitBitmap               = 0x00000003
WHvCapabilityCodeX64MsrExitBitmap                  = 0x00000004
WHvCapabilityCodeGpaRangePopulateFlags             = 0x00000005
WHvCapabilityCodeSchedulerFeatures                 = 0x00000006
WHvCapabilityCodeProcessorVendor                   = 0x00001000
WHvCapabilityCodeProcessorFeatures                 = 0x00001001
WHvCapabilityCodeProcessorClFlushSize              = 0x00001002
WHvCapabilityCodeProcessorXsaveFeatures            = 0x00001003
WHvCapabilityCodeProcessorClockFrequency           = 0x00001004
WHvCapabilityCodeInterruptClockFrequency           = 0x00001005
WHvCapabilityCodeProcessorFeaturesBanks            = 0x00001006
WHvCapabilityCodeProcessorFrequencyCap             = 0x00001007
WHvCapabilityCodeSyntheticProcessorFeaturesBanks   = 0x00001008
WHvCapabilityCodeProcessorPerfmonFeatures          = 0x00001009
WHvCapabilityCodePhysicalAddressWidth              = 0x0000100A

WHvPartitionPropertyCodeProcessorCount             = 0x00001FFF
WHvPartitionPropertyCodeExtendedVmExits            = 0x00000001
WHvPartitionPropertyCodeExceptionExitBitmap        = 0x00000002

; WHP processor vendors.
WHvProcessorVendorAmd   = 0x00000000
WHvProcessorVendorIntel = 0x00000001
WHvProcessorVendorHygon = 0x00000002

; WHP GPA mapping flags.
WHvMapGpaRangeFlagRead    = 0x00000001
WHvMapGpaRangeFlagWrite   = 0x00000002
WHvMapGpaRangeFlagExecute = 0x00000004

; WHP x64 register names used in starter examples.
WHvX64RegisterRax    = 0x00000000
WHvX64RegisterRcx    = 0x00000001
WHvX64RegisterRdx    = 0x00000002
WHvX64RegisterRbx    = 0x00000003
WHvX64RegisterRsp    = 0x00000004
WHvX64RegisterRbp    = 0x00000005
WHvX64RegisterRsi    = 0x00000006
WHvX64RegisterRdi    = 0x00000007
WHvX64RegisterRip    = 0x00000010
WHvX64RegisterRflags = 0x00000011
WHvX64RegisterEs     = 0x00000012
WHvX64RegisterCs     = 0x00000013
WHvX64RegisterSs     = 0x00000014
WHvX64RegisterDs     = 0x00000015
WHvX64RegisterFs     = 0x00000016
WHvX64RegisterGs     = 0x00000017
WHvX64RegisterCr0    = 0x0000001C
WHvX64RegisterCr3    = 0x0000001E
WHvX64RegisterCr4    = 0x0000001F

; WHP run exit reason used in starter examples.
WHvRunVpExitReasonMemoryAccess    = 0x00000001
WHvRunVpExitReasonX64IoPortAccess = 0x00000002
WHvRunVpExitReasonException       = 0x00001002
WHvRunVpExitReasonX64Halt = 0x00000008




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

