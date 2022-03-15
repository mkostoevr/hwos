#pragma once

#define ADDR32_MIN 0x00000000
#define ADDR32_MAX 0xFFFFFFFF
#define ADDR64_MIN 0x0000000000000000LLU
#define ADDR64_MAX 0xFFFFFFFFFFFFFFFFLLU

// SDM Vol. 3 Ch. 2.3 System flags and fields in the EFLAGS register
// Figure 2-5. System Flags in the EFLAGS Register
#define EFLAGS_CF    (1 << 0)
#define EFLAGS_PF    (1 << 2)
#define EFLAGS_AF    (1 << 4)
#define EFLAGS_ZF    (1 << 6)
#define EFLAGS_SF    (1 << 7)
#define EFLAGS_TF    (1 << 8)  // Trap
#define EFLAGS_IF    (1 << 9)  // Interrupt Enable
#define EFLAGS_DF    (1 << 10)
#define EFLAGS_OF    (1 << 11)
#define EFLAGS_IOPL ((1 << 12) | (1 << 13)) // I/O privilege level field
#define EFLAGS_NT    (1 << 14) // Nested task
#define EFLAGS_RF    (1 << 16) // Resume
#define EFLAGS_VM    (1 << 17) // Virtual-8086 mode
#define EFLAGS_AC    (1 << 18) // Alignment check or access control
#define EFLAGS_VIF   (1 << 19) // Virtual interrupt
#define EFLAGS_VIP   (1 << 20) // Virtual interrupt pending
#define EFLAGS_ID    (1 << 21) // Identification

// SDM Vol. 3 Ch. 2.5 Control registers
// Figure 2-7. Control Registers
#define CR4_VME        (1 << 0)  // Virtual-8086 Mode Extensions
#define CR4_PVI        (1 << 1)  // Protected-Mode Virtual Interrupts
#define CR4_TSD        (1 << 2)  // Time Stamp Disable
#define CR4_DE         (1 << 3)  // Debugging Extensions
#define CR4_PSE        (1 << 4)  // Page Size Extensions
#define CR4_PAE        (1 << 5)  // Physical Address Extension
#define CR4_MCE        (1 << 6)  // Machine-Check Enable
#define CR4_PGE        (1 << 7)  // Page Global Enable
#define CR4_PCE        (1 << 8)  // Performance-Monitoring Counter Enable
#define CR4_OSFXSR     (1 << 9)  // Operating System Support for FXSAVE and
                                 // FXRSTOR instructions
#define CR4_OSXMMEXCPT (1 << 10) // Operating System Support for Unmasked SIMD
                                 // Floating-Point Exceptions
#define CR4_UMIP       (1 << 11) // User-Mode Instruction Prevention
#define CR4_LA57       (1 << 12) // 57-bit linear addresses
#define CR4_VMXE       (1 << 13) // VMX-Enable Bit
#define CR4_SMXE       (1 << 14) // SMX-Enable Bit
#define CR4_FSGSBASE   (1 << 16) // FSGSBASE-Enable Bit
#define CR4_PCIDE      (1 << 17) // PCID-Enable Bit
#define CR4_OSXSAVE    (1 << 18) // XSAVE and Processor Extended States-Enable
                                 // Bit
#define CR4_SMEP       (1 << 20) // SMEP-Enable Bit
#define CR4_SMAP       (1 << 21) // SMAP-Enable Bit
#define CR4_PKE        (1 << 22) // Enable protection keys for user-mode pages
#define CR4_CET        (1 << 23) // Control-flow Enforcement Technology
#define CR4_PKS        (1 << 24) // Enable protection keys for supervisor-mode
                                 // pages

#define CR3_PWT (1 << 3) // Page-level Write-Through
#define CR3_PCD (1 << 4) // Page-level Cache Disable
#define CR3_PAGE_DIRECTORY_BASE_64 0xfffffffffffff000
#define CR3_PAGE_DIRECTORY_BASE_32 0xfffff000

#define CR0_PE (1 << 0)  // Protection Enable
#define CR0_MP (1 << 1)  // Monitor Coprocessor
#define CR0_EM (1 << 2)  // Emulation
#define CR0_TS (1 << 3)  // Task Switched
#define CR0_ET (1 << 4)  // Extension Type
#define CR0_NE (1 << 5)  // Numeric Error
#define CR0_WP (1 << 16) // Write Protect
#define CR0_AM (1 << 18) // Alignment Mask
#define CR0_NW (1 << 29) // Non Write-through
#define CR0_CD (1 << 30) // Cache Disable
#define CR0_PG (1 << 31) // Paging

// SDM Vol. 3 Ch. 2.6 Extended control registers
// Figure 2-8. XCR0
#define XCR0_X86_FPU_MMX_STATE (1 << 0)
#define XCR0_SSE_STATE         (1 << 1)
#define XCR0_AVX_STATE         (1 << 2)
#define XCR0_BNDREG_STATE      (1 << 3)
#define XCR0_BNDCSR_STATE      (1 << 4)
#define XCR0_OPMASK_STATE      (1 << 5)
#define XCR0_ZMM_HI256_STATE   (1 << 6)
#define XCR0_HI16_ZMM_STATE    (1 << 7)
#define XCR0_PKRU_STATE        (1 << 9)

// SDM Vol. 3 Ch. 3.4.2 Segment selectors
// Figure 3-6. Segment Selector
#define SS_INDEX     0xfff8
#define SS_TI        0x0004 // Table indicator
#define SS_TI_GDT    0x0000
#define SS_TI_LDT    0x0004
#define SS_RPL       0x0003 // Requested Privilige Level
#define SS_RPL_RING0 0x0000
#define SS_RPL_RING1 0x0001
#define SS_RPL_RING2 0x0002
#define SS_RPL_RING3 0x0003
#define SS(INDEX) (INDEX << 3)

// SDM Vol. 3 Ch. 3.4.5 Segment descriptors
// Figure 3-8. Segment Descriptor
#define SD_D0_SEGMENT_LIMIT_15_00 0x0000ffff
#define SD_D0_BASE_ADDRESS_15_00  0xffff0000
#define SD_D1_BASE_23_16          0x000000ff
#define SD_D1_TYPE                0x00000f00
#define SD_D1_S                   0x00001000
#define SD_D1_S_SYSTEM            0x00000000
#define SD_D1_S_CODE_OR_DATA      0x00001000
#define SD_D1_DPL                 0x00006000
#define SD_D1_DPL_RING0           0x00000000
#define SD_D1_DPL_RING1           0x00002000
#define SD_D1_DPL_RING2           0x00004000
#define SD_D1_DPL_RING3           0x00006000
#define SD_D1_PRESENT             0x00008000
#define SD_D1_SEG_LIMIT_19_16     0x000f0000
#define SD_D1_AVL                 0x00100000
#define SD_D1_L                   0x00200000
#define SD_D1_DB                  0x00400000
#define SD_D1_DB_16BIT_SEGMENT    0x00000000
#define SD_D1_DB_32BIT_SEGMENT    0x00400000
#define SD_D1_GRANULARITY         0x00800000
#define SD_D1_BASE_31_24          0xff000000

// SDM Vol. 3 Ch. 3.4.5.1 Code- ad data-segment descriptor types
// Table 3-1. Code- and Data-Segment Types
#define SD_D1_TYPE_DATA   0x00000000
#define SD_D1_TYPE_DATA_E 0x00000400
#define SD_D1_TYPE_DATA_W 0x00000200
#define SD_D1_TYPE_DATA_A 0x00000100
#define SD_D1_TYPE_CODE   0x00000800
#define SD_D1_TYPE_CODE_C 0x00000400
#define SD_D1_TYPE_CODE_R 0x00000200
#define SD_D1_TYPE_CODE_A 0x00000100

// SDM Vol. 3 Ch. 3.5 System descriptor types
// Table 3-2. System-Segment and Gate-Sescriptor Types
#define SD_D1_TYPE_SYSTEM_16BIT_TSS_AVAILABLE  0x00000100
#define SD_D1_TYPE_SYSTEM_LDT                  0x00000200
#define SD_D1_TYPE_SYSTEM_16BIT_TSS_BUSY       0x00000300
#define SD_D1_TYPE_SYSTEM_16BIT_CALL_GATE      0x00000400
#define SD_D1_TYPE_SYSTEM_TASK_GATE            0x00000500
#define SD_D1_TYPE_SYSTEM_16BIT_INTERRUPT_GATE 0x00000600
#define SD_D1_TYPE_SYSTEM_16BIT_TRAP_GATE      0x00000700
#define SD_D1_TYPE_SYSTEM_32BIT_TSS_AVAILABLE  0x00000900
#define SD_D1_TYPE_SYSTEM_32BIT_TSS_BUSY       0x00000B00
#define SD_D1_TYPE_SYSTEM_32BIT_CALL_GATE      0x00000C00
#define SD_D1_TYPE_SYSTEM_32BIT_INTERRUPT_GATE 0x00000E00
#define SD_D1_TYPE_SYSTEM_32BIT_TRAP_GATE      0x00000F00
