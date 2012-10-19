﻿#pragma once

#define STATUS_IE		0x00000000
#define STATUS_EXL		0x00000002
#define STATUS_ERL		0x00000004
#define STATUS_KSU		0x00000018
#define STATUS_UX		0x00000020
#define STATUS_SX		0x00000040
#define STATUS_KX		0x00000080
#define STATUS_IM		0x0000FF00
#define STATUS_DE		0x00010000
#define STATUS_CE		0x00020000
#define STATUS_CH		0x00040000
#define STATUS_SR		0x00100000
#define STATUS_TS		0x00200000
#define STATUS_BEV		0x00400000
#define STATUS_rsvd		0x00800000
#define STATUS_ITS		0x01000000
#define STATUS_RE		0x02000000
#define STATUS_FR		0x04000000
#define STATUS_RP		0x08000000
#define STATUS_CU		0xF0000000

#define CAUSE_ExcCode	0x0000007C
#define CAUSE_IP		0x0000FF00
#define CAUSE_CE		0x30000000
#define CAUSE_BD		0x10000000

#define CAUSE_IP0		0x00000100
#define CAUSE_IP1		0x00000200
#define CAUSE_IP2		0x00000400
#define CAUSE_IP3		0x00000800
#define CAUSE_IP4		0x00001000
#define CAUSE_IP5		0x00002000
#define CAUSE_IP6		0x00004000
#define CAUSE_IP7		0x00008000

#define MI_INTR_SP		0x01		/* Bit 0: SP intr */
#define MI_INTR_SI		0x02		/* Bit 1: SI intr */
#define MI_INTR_AI		0x04		/* Bit 2: AI intr */
#define MI_INTR_VI		0x08		/* Bit 3: VI intr */
#define MI_INTR_PI		0x10		/* Bit 4: PI intr */
#define MI_INTR_DP		0x20		/* Bit 5: DP intr */

enum Exception
{
	INTERRUPT						= 0,
	TLB_MODIFIED_DATA_WRITE			= 1,
	TLB_INVALID_INSTRUCTION_FETCH	= 2,
	TLB_INVALID_DATA_ACCESS			= 3,
	ADDRESS_ERROR_INSTRUCTION_FETCH = 4,
	ADDRESS_ERROR_DATA_ACCESS		= 5,
	BUS_ERROR_INSTRUCTION_FETCH		= 6,
	BUS_ERROR_DATA_ACCESS			= 7,
	SYSTEM_CALL						= 8,
	BREAKPOINT						= 9,
	RESERVED_INSTRUCTION			= 10,
	COPROCESSOR_UNUSABLE			= 11,
	INTEGER_OVERFLOW				= 12,
	TRAP_INSTRUCTION				= 13,
	FLOATING_POINT_EXCEPTION		= 15,
	WATCH							= 23,

	RESET,
	SOFT_RESET,
	NMI,
	TLB_REFILL_INSTRUCTION_FETCH,
	TLB_REFILL_DATA_ACCESS,
};

enum InterruptType
{
	SW1		= CAUSE_IP0,	// Software level 1 pending
	SW2		= CAUSE_IP1,	// Software level 2 pending
	HW0		= CAUSE_IP2,	// External level 3 pending - INT0
	HW1		= CAUSE_IP3,	// External level 4 pending - INT1
	HW2		= CAUSE_IP4,	// External level 5 pending - INT2
	HW3		= CAUSE_IP5,	// External level 6 pending - INT3
	HW4		= CAUSE_IP6,	// External level 7 pending - INT4
	COMPARE	= CAUSE_IP7		// External level 8 pending - COMPARE
};