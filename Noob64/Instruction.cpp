/*
 * Noob64 - A Nintendo 64 emulator.
 *
 * (c) Copyright 2012 Quentin Metzler and 
 * Romain Richard.
 *
 * Permission to use, copy, modify and distribute Noob64 in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Noob64 is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#include "StdAfx.h"
#include "R4300i.h"

//****************************************************************************
//** DECODE METHODS															**
//****************************************************************************

void R4300i::decode(const word i)
{
	switch(getOpCode(i)) {
	case 0:
		decode_r(i);
		break;
	case 1:
		decode_i(i);
		break;
	case 2:
		J(getTarget(i));
		break;
	case 3:
		JAL(getTarget(i));
		break;
	case 4:
		BEQ(getRs(i), getRt(i), getImmediate(i));
		break;
	case 5:
		BNE(getRs(i), getRt(i), getImmediate(i));
		break;
	case 6:
		BLEZ(getRs(i), getImmediate(i));
		break;
	case 7:
		BGTZ(getRs(i), getImmediate(i));
		break;
	case 8:
		ADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 9:
		ADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 10:
		SLTI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 11:
		SLTIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 12:
		ANDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 13:
		ORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 14:
		XORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 15:
		LUI(getRt(i), getImmediate(i));
		break;
	case 16:
		decode_cop0(i);
		break;
	case 17:
		decode_cop1(i);
		break;
	case 20:
		BEQL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 21:
		BNEL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 22:
		BLEZL(getImmediate(i), getRs(i));
		break;
	case 23:
		BGTZL(getImmediate(i), getRs(i));
		break;
	case 24:
		DADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 25:
		DADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 26:
		LDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 27:
		LDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 32:
		LB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 33:
		LH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 34:
		LWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 35:
		LW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 36:
		LBU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 37:
		LHU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 38:
		LWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 39:
		LWU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 40:
		SB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 41:
		SH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 42:
		SWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 43:
		SW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 44:
		SDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 45:
		SDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 46:
		SWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 47:
		CACHE(getRt(i), getImmediate(i), getRs(i));
		break;
	case 48:
		LL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 49:
		LWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 52:
		LLD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 53:
		LDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 54:
		//TODO: LDC2
		break;
	case 55:
		LD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 56:
		SC(getRt(i), getImmediate(i), getRs(i));
		break;
	case 57:
		SWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 60:
		SCD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 61:
		SDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 62:
		//TODO: SDC2
		break;
	case 63:
		SD(getRt(i), getImmediate(i), getRs(i));
		break;
	default:
		trigger_address_error(i, true);
	}
}

inline void R4300i::decode_r(word i)
{
	switch(getFunct(i)) {
	case 0:
		SLL(getRd(i), getRt(i), getSa(i));
		break;
	case 2:
		SRL(getRd(i), getRt(i), getSa(i));
		break;
	case 3:
		SRA(getRd(i), getRt(i), getSa(i));
		break;
	case 4:
		SLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 6:
		SRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 7:
		SRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 8:
		JR(getRs(i));
		break;
	case 9:
		JALR(getRs(i), getRd(i));
		break;
	case 12:
		SYSCALL(getImmediate(i));
		break;
	case 13:
		BREAK(getImmediate(i));
		break;
	case 15:
		SYNC();
		break;
	case 16:
		MFHI(getRd(i));
		break;
	case 17:
		MTHI(getRs(i));
		break;
	case 18:
		MFLO(getRd(i));
		break;
	case 19:
		MTLO(getRs(i));
		break;
	case 20:
		DSLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 22:
		DSRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 23:
		DSRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 24:
		MULT(getRs(i), getRt(i));
		break;
	case 25:
		MULTU(getRs(i), getRt(i));
		break;
	case 26:
		DIV(getRs(i), getRt(i));
		break;
	case 27:
		DIVU(getRs(i), getRt(i));
		break;
	case 28:
		DMULT(getRs(i), getRt(i));
		break;
	case 29:
		DMULTU(getRs(i), getRt(i));
		break;
	case 30:
		DDIV(getRs(i), getRt(i));
		break;
	case 31:
		DDIVU(getRs(i), getRt(i));
		break;
	case 32:
		ADD(getRd(i), getRs(i), getRt(i));
		break;
	case 33:
		ADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 34:
		SUB(getRd(i), getRs(i), getRt(i));
		break;
	case 35:
		SUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 36:
		AND(getRd(i), getRs(i), getRt(i));
		break;
	case 37:
		OR(getRd(i), getRs(i), getRt(i));
		break;
	case 38:
		XOR(getRd(i), getRs(i), getRt(i));
		break;
	case 39:
		NOR(getRd(i), getRs(i), getRt(i));
		break;
	case 42:
		SLT(getRd(i), getRs(i), getRt(i));
		break;
	case 43:
		SLTU(getRd(i), getRs(i), getRt(i));
		break;
	case 44:
		DADD(getRd(i), getRs(i), getRt(i));
		break;
	case 45:
		DADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 46:
		DSUB(getRd(i), getRs(i), getRt(i));
		break;
	case 47:
		DSUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 48:
		TGE(getRs(i), getRt(i));
		break;
	case 49:
		TGEU(getRs(i), getRt(i));
		break;
	case 50:
		TLT(getRs(i), getRt(i));
		break;
	case 51:
		TLTU(getRs(i), getRt(i));
		break;
	case 52:
		TEQ(getRs(i), getRt(i));
		break;
	case 54:
		TNE(getRs(i), getRt(i));
		break;
	case 56:
		DSLL(getRd(i), getRt(i), getSa(i));
		break;
	case 58:
		DSRL(getRd(i), getRt(i), getSa(i));
		break;
	case 59:
		DSRA(getRd(i), getRt(i), getSa(i));
		break;
	case 60:
		DSLL32(getRd(i), getRt(i), getSa(i));
		break;
	case 62:
		DSRL32(getRd(i), getRt(i), getSa(i));
		break;
	case 63:
		DSRA32(getRd(i), getRt(i), getSa(i));
		break;
	default:
		trigger_address_error(i, true);
	}
}

inline void R4300i::decode_i(word i)
{
	switch(getRt(i)) {
	case 0:
		BLTZ(getImmediate(i), getRs(i));
		break;
	case 1:
		BGEZ(getImmediate(i), getRs(i));
		break;
	case 2:
		BLTZL(getImmediate(i), getRs(i));
		break;
	case 3:
		BGEZL(getImmediate(i), getRs(i));
		break;
	case 8:
		TGEI(getRs(i), getImmediate(i));
		break;
	case 9:
		TGEIU(getRs(i), getImmediate(i));
		break;
	case 10:
		TLTI(getRs(i), getImmediate(i));
		break;
	case 11:
		TLTIU(getRs(i), getImmediate(i));
		break;
	case 12:
		TEQI(getRs(i), getImmediate(i));
		break;
	case 14:
		TNEI(getRs(i), getImmediate(i));
		break;
	case 16:
		BLTZAL(getImmediate(i), getRs(i));
		break;
	case 17:
		BGEZAL(getImmediate(i), getRs(i));
		break;
	case 18:
		BLTZALL(getImmediate(i), getRs(i));
		break;
	case 19:
		BGEZALL(getImmediate(i), getRs(i));
		break;
	default:
		trigger_address_error(i, true);
	}
}

inline void R4300i::decode_cop0(word i)
{
	current_coprocessor = COP0;

	switch(getRs(i)) {
	case 0:
		MFC0(getRt(i), getRd(i));
		break;
	case 4:
		MTC0(getRt(i), getRd(i));
		break;
	case 16:
		decode_tlb(i);
		break;
	default:
		trigger_address_error(i, true);
	}

	current_coprocessor = CPU;
}

inline void R4300i::decode_tlb(word i)
{
	switch(getFunct(i)) {
	case 1:
		TLBR();
		break;
	case 2:
		TLBWI();
		break;
	case 6:
		TLBWR();
		break;
	case 8:
		TLBP();
		break;
	case 24:
		ERET();
		break;
	default:
		trigger_address_error(i, true);
	}
}

inline void R4300i::decode_cop1(const word i)
{
	current_coprocessor = COP1;

	switch(getRs(i)) {
	case 0:
		MFC1(getRt(i), getRd(i));
		break;
	case 1:
		DMFC1(getRt(i), getRd(i));
		break;
	case 2:
		CFC1(getRt(i), getRd(i));
		break;
	case 4:
		MTC1(getRt(i), getRd(i));
		break;
	case 5:
		DMTC1(getRt(i), getRd(i));
		break;
	case 6:
		CTC1(getRt(i), getRd(i));
		break;
	case 8:
		decode_bc1(i);
		break;
	case 16:
		decode_fpu<s>(i);
		break;
	case 17:
		decode_fpu<d>(i);
		break;
	case 20:
		decode_fpu<w>(i);
		break;
	case 21:
		decode_fpu<l>(i);
		break;
	default:
		trigger_address_error(i, true);
	}

	current_coprocessor = CPU;
}

inline void R4300i::decode_bc1(const word i)
{
	switch(getNdTf(i)) {
	case 0:
		BC1F(getImmediate(i));
		break;
	case 1:
		BC1T(getImmediate(i));
		break;
	case 2:
		BC1FL(getImmediate(i));
		break;
	case 3:
		BC1TL(getImmediate(i));
		break;
	default:
		trigger_address_error(i, true);
	}
}

template<typename Type>
inline void R4300i::decode_fpu(const word i)
{
	switch(getFunct(i)) {
	case 0:
		ADD<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 1:
		SUB<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 2:
		MUL<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 3:
		DIV<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 4:
		SQRT<Type>(getSa(i), getRd(i));
		break;
	case 5:
		ABS<Type>(getSa(i), getRd(i));
		break;
	case 6:
		MOV<Type>(getSa(i), getRd(i));
		break;
	case 7:
		NEG<Type>(getSa(i), getRd(i));
		break;
	case 8:
		ROUND<Type, l>(getSa(i), getRd(i));
		break;
	case 9:
		TRUNC<Type, l>(getSa(i), getRd(i));
		break;
	case 10:
		CEIL<Type, l>(getSa(i), getRd(i));
		break;
	case 11:
		FLOOR<Type, l>(getSa(i), getRd(i));
		break;
	case 12:
		ROUND<Type, w>(getSa(i), getRd(i));
		break;
	case 13:
		TRUNC<Type, w>(getSa(i), getRd(i));
		break;
	case 14:
		CEIL<Type, w>(getSa(i), getRd(i));
		break;
	case 15:
		FLOOR<Type, w>(getSa(i), getRd(i));
		break;
	case 32:
		CVT<Type, s>(getSa(i), getRd(i));
		break;
	case 33:
		CVT<Type, d>(getSa(i), getRd(i));
		break;
	case 36:
		CVT<Type, w>(getSa(i), getRd(i));
		break;
	case 37:
		CVT<Type, l>(getSa(i), getRd(i));
		break;
	case 48:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 49:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 50:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 51:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 52:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 53:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 54:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 55:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 56:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 57:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 58:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 59:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 60:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 61:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 62:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 63:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	default:
		trigger_address_error(i, true);
	}
}

//****************************************************************************
//** INSTRUCTIONS															**
//****************************************************************************

#if defined DEBUG
#	define PRINT_PC(instr) cout << print_addr((word) pc) << instr
#	define PRINT(instr) cout << instr
#else
#	define PRINT_PC(instr)
#	define PRINT(instr)
#endif

void R4300i::LB(int rt, int immed, int rs)
{
	PRINT_PC("LB " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_byte(memory->read<sbyte>(r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LBU(int rt, int immed, int rs)
{
	PRINT_PC("LBU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = memory->read<byte>(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LD(int rt, int immed, int rs)
{
	PRINT_PC("LD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = memory->read<dword>(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LDL(int rt, int immed, int rs)
{
	PRINT_PC("LDL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	dword tmp = memory->read<dword>(r[rs] + extend_sign_halfword(immed));
	r[rt] |= (tmp << ((r[rs] + extend_sign_halfword(immed)) & 7) * 8);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LDR(int rt, int immed, int rs)
{
	PRINT_PC("LDR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	dword tmp = memory->read<dword>(r[rs] + extend_sign_halfword(immed));
	r[rt] |= (tmp >> (( 7 - (r[rs] + extend_sign_halfword(immed)) & 7)) * 8);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LH(int rt, int immed, int rs)
{
	PRINT_PC("LH " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_halfword(memory->read<shword>(r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LHU(int rt, int immed, int rs)
{
	PRINT_PC("LHU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = memory->read<hword>(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LL(int rt, int immed, int rs)
{
	PRINT_PC("LL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(memory->read<sword>(r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	ll = 1;
	pc += 4;
}

void R4300i::LLD(int rt, int immed, int rs)
{
	PRINT_PC("LLD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = memory->read<sdword>(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	ll = 1;
	pc += 4;
}

void R4300i::LW(int rt, int immed, int rs)
{
	PRINT_PC("LW " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(memory->read<word>(r[rs] + extend_sign_halfword(immed)));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LWL(int rt, int immed, int rs)
{
	PRINT_PC("LWL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	word tmp = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	r[rt] |= (tmp << (3 - (r[rs] + extend_sign_halfword(immed)) & 3) * 8);
	r[rt] = extend_sign_word(r[rt]);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LWR(int rt, int immed, int rs)
{
	PRINT_PC("LWR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	word tmp = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	r[rt] |= (tmp >> ((3 - (r[rs] + extend_sign_halfword(immed)) & 3)) * 8);
	r[rt] = extend_sign_word(r[rt]);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::LWU(int rt, int immed, int rs)
{
	PRINT_PC("LWU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::SB(int rt, int immed, int rs)
{
	PRINT_PC("SB " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	memory->write<byte>(r[rt] & 0xFF, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SC(int rt, int immed, int rs)
{
	if (ll)
	{
		PRINT_PC("SC " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
		memory->write<word>(r[rt] & 0xFFFFFFFF, r[rs] + extend_sign_halfword(immed));
		//maybe something to do here...
		ll = 0;
	}
	else
		PRINT_PC("SC " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]  no ll was done before");
	pc += 4;
}

void R4300i::SCD(int rt, int immed, int rs)
{
	if (ll)
	{
	PRINT_PC("SCD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
		memory->write<dword>(r[rt], r[rs] + extend_sign_halfword(immed));
		//maybe something to do here...
		ll = 0;
	}
	else
	{
	PRINT_PC("SCD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]  no ll was done before");
	}
	pc += 4;
}

void R4300i::SD(int rt, int immed, int rs)
{
	PRINT_PC("SD " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	memory->write<dword>(r[rt], r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SDL(int rt, int immed, int rs)
{
	dword old_word = 0;
	PRINT_PC("SDL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = memory->read<dword>(r[rs] + extend_sign_halfword(immed));
	old_word = (r[rt] >> (8 * (r[rs] + extend_sign_halfword(immed)) & 7)) | old_word;
	memory->write<dword>(old_word, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SDR(int rt, int immed, int rs)
{
	dword old_word = 0;
	PRINT_PC("SDR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = memory->read<dword>(r[rs] + extend_sign_halfword(immed));
	old_word = (r[rt] << (8 * (7 - (r[rs] + extend_sign_halfword(immed)) & 7))) | old_word;
	memory->write<dword>(old_word, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SH(int rt, int immed, int rs)
{
	PRINT_PC("SH " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	memory->write<hword>(r[rt] & 0xFFFF, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SW(int rt, int immed, int rs)
{
	PRINT_PC("SW " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	memory->write<word>(r[rt] & 0xFFFFFFFF, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SWL(int rt, int immed, int rs)
{
	word old_word = 0;
	PRINT_PC("SWL " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	old_word = (r[rt] >> (8 * (r[rs] + extend_sign_halfword(immed)) & 3)) & 0xFFFFFFFF | old_word;
	memory->write<word>(old_word, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SWR(int rt, int immed, int rs)
{
	word old_word = 0;
	PRINT_PC("SWR " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	old_word = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	old_word = (r[rt] << (8 * (3 - (r[rs] + extend_sign_halfword(immed)) & 3))) & 0xFFFFFFFF | old_word;
	memory->write<word>(old_word, r[rs] + extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::SYNC(void)
{
	PRINT_PC("SYNC?");
	pc += 4;
}

void R4300i::ADD(int rd, int rs, int rt)
{
#	if defined DEBUG
		if (!rt) { PRINT_PC("MOVE " << dec << "r" << rd << ", " << dec << "r" << rs); }
		else PRINT_PC("ADD " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif
	r[rd] = extend_sign_word(r[rs] + r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::ADDI(int rt, int rs, int immed)
{
	PRINT_PC("ADDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::ADDIU(int rt, int rs, int immed)
{
	PRINT_PC("ADDIU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << dec << "[" << dec << "r" << rs << "]");
	r[rt] = extend_sign_word(r[rs] + extend_sign_halfword(immed));
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::ADDU(int rd, int rs, int rt)
{
	PRINT_PC("ADDU " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = extend_sign_word(r[rs] + r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::AND(int rd, int rs, int rt)
{
	PRINT_PC("AND " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] & r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::ANDI(int rt, int rs, int immed)
{
	PRINT_PC("ANDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] & immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::DADD(int rd, int rs, int rt)
{
	PRINT_PC("DADD " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] + r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DADDI(int rt, int rs, int immed)
{
	PRINT_PC("DADDI " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] + extend_sign_halfword(immed);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::DADDIU(int rt, int rs, int immed)
{
	PRINT_PC("DADDIU " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << "[" << dec << "r" << rs << "]");
	r[rt] = r[rs] + extend_sign_halfword(immed);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::DADDU(int rd, int rs, int rt)
{
	PRINT_PC("DADDU " << dec << "r" << rd << ", " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] + r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DDIV(int rs, int rt)
{
	PRINT_PC("DDIV " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = (sdword) r[rs] / (sdword) r[rt];
	hi = (sdword) r[rs] % (sdword) r[rt];
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DDIVU(int rs, int rt)
{
	PRINT_PC("DDIVU " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = r[rs] / r[rt];
	hi = r[rs] % r[rt];
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DIV(int rs, int rt)
{
	PRINT_PC("DIV " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = extend_sign_word(r[rs] / r[rt]);
	hi = extend_sign_word(r[rs] % r[rt]);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DIVU(int rs, int rt)
{
	PRINT_PC("DIVU " << dec << "r" << rs << ", " << dec << "r" << rt);
	lo = extend_sign_word(r[rs] / r[rt]);
	hi = extend_sign_word(r[rs] % r[rt]);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DMULT(int rs, int rt)
{
	PRINT_PC("DMULT " << dec << "r" << rs << ", " << dec << "r" << rt);
	dword op1, op2, op3, op4;
	dword result1, result2, result3, result4;
	dword temp1, temp2, temp3, temp4;
	int sign = 0;

	if (r[rs] < 0)
	{
		op2 = - (sdword) r[rs];
		sign = 1 - sign;
	}
	else
		op2 = r[rs];
	if (r[rt] < 0)
	{
		op4 = - (sdword) r[rt];
		sign = 1 - sign;
	}
	else
		op4 = r[rt];

	op1 = op2 & 0xFFFFFFFF;
	op2 = (op2 >> 32) & 0xFFFFFFFF;
	op3 = op4 & 0xFFFFFFFF;
	op4 = (op4 >> 32) & 0xFFFFFFFF;

	temp1 = op1 * op3;
	temp2 = (temp1 >> 32) + op1 * op4;
	temp3 = op2 * op3;
	temp4 = (temp3 >> 32) + op2 * op4;

	result1 = temp1 & 0xFFFFFFFF;
	result2 = temp2 + (temp3 & 0xFFFFFFFF);
	result3 = (result2 >> 32) + temp4;
	result4 = (result3 >> 32);

	lo = result1 | (result2 << 32);
	hi = (result3 & 0xFFFFFFFF) | (result4 << 32);
	if (sign)
	{
		hi = ~hi;
		if (!lo)
			hi++;
		else
			lo = ~lo + 1;
	}
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DMULTU(int rs, int rt)
{
	PRINT_PC("DMULTU " << dec << "r" << rs << ", " << dec << "r" << rt);
	dword op1, op2, op3, op4;
	dword result1, result2, result3, result4;
	dword temp1, temp2, temp3, temp4;

	op1 = r[rs] & 0xFFFFFFFF;
	op2 = (r[rs] >> 32) & 0xFFFFFFFF;
	op3 = r[rt] & 0xFFFFFFFF;
	op4 = (r[rt] >> 32) & 0xFFFFFFFF;

	temp1 = op1 * op3;
	temp2 = (temp1 >> 32) + op1 * op4;
	temp3 = op2 * op3;
	temp4 = (temp3 >> 32) + op2 * op4;

	result1 = temp1 & 0xFFFFFFFF;
	result2 = temp2 + (temp3 & 0xFFFFFFFF);
	result3 = (result2 >> 32) + temp4;
	result4 = (result3 >> 32);

	lo = result1 | (result2 << 32);
	hi = (result3 & 0xFFFFFFFF) | (result4 << 32);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::DSLL(int rd, int rt, int sa)
{
	PRINT_PC("DSLL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] << sa;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSLL32(int rd, int rt, int sa)
{
	PRINT_PC("DSLL32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] << (sa + 32);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSLLV(int rd, int rt, int rs)
{
	PRINT_PC("DSLLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = r[rt] << r[rs];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRA(int rd, int rt, int sa)
{
	PRINT_PC("DSRA " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> sa;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRA32(int rd, int rt, int sa)
{
	PRINT_PC("DSRA32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> (sa + 32);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRAV(int rd, int rt, int rs)
{
	PRINT_PC("DSRAV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = r[rt] >> r[rs];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRL(int rd, int rt, int sa)
{
	PRINT_PC("DSRL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> sa;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRL32(int rd, int rt, int sa)
{
	PRINT_PC("DSRL32 " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = r[rt] >> (sa + 32);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSRLV(int rd, int rt, int rs)
{
	PRINT_PC("DSRLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = r[rt] >> r[rs];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSUB(int rd, int rs, int rt)
{
	PRINT_PC("DSUB " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = (sdword) r[rs] - (sdword) r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::DSUBU(int rd, int rs, int rt)
{
	PRINT_PC("DSUBU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] - r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::LUI(int rt, int immed)
{
	PRINT_PC("LUI " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed));
	r[rt] = extend_sign_word(extend_sign_halfword(immed) << 16);
	PRINT(" r" << dec << rt << "=0x" << hex << r[rt]);
	pc += 4;
}

void R4300i::MFHI(int rd)
{
	PRINT_PC("MFHI " << dec << "r" << rd);
	r[rd] = hi;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::MFLO(int rd)
{
	PRINT_PC("MFLO " << dec << "r" << rd);
	r[rd] = lo;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::MTHI(int rs)
{
	PRINT_PC("MTHI " << dec << "r" << rs);
	hi = r[rs];
	PRINT_PC(" hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::MTLO(int rs)
{
	PRINT_PC("MTLO " << dec << "r" << rs);
	lo = r[rs];
	PRINT_PC(" lo" << hex << "=0x" << lo);
	pc += 4;
}

void R4300i::MULT(int rs, int rt)
{
	PRINT_PC("MULT " << dec << "r" << rs << ", " << dec << "r" << rt);
	sdword temp = r[rs] * r[rt];
	hi = extend_sign_word(temp >> 32);
	lo = extend_sign_word(temp);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::MULTU(int rs, int rt)
{
	PRINT_PC("DMULTU " << dec << "r" << rs << ", " << dec << "r" << rt);
	dword temp = r[rs] * r[rt];
	hi = extend_sign_word(temp >> 32);
	lo = extend_sign_word(temp);
	PRINT_PC(" lo" << hex << "=0x" << lo << " hi" << hex << "=0x" << hi);
	pc += 4;
}

void R4300i::NOR(int rd, int rs, int rt)
{
	PRINT_PC("NOR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = ~(r[rs] | r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::OR(int rd, int rs, int rt)
{
	PRINT_PC("OR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] | r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::ORI(int rt, int rs, int immed)
{
	PRINT_PC("ORI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	r[rt] = r[rs] | immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::SLL(int rd, int rt, int sa)
{
#	if defined DEBUG
		if (!rd && !rt && !sa) { PRINT_PC("NOP"); }
		else PRINT_PC("SLL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
#	endif
	r[rd] = extend_sign_word((word) r[rt] << sa);

#	if defined DEBUG
		if (!rd && !rt && !sa) { }
		else PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
#	endif
	pc += 4;
}

void R4300i::SLLV(int rd, int rt, int rs)
{
	PRINT_PC("SLLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((word) r[rt] << (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SLT(int rd, int rs, int rt)
{
	PRINT_PC("SLT " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	if ((sword) r[rs] < (sword) r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SLTI(int rt, int rs, int immed)
{
	PRINT_PC("SLTI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	if ((sword) r[rs] < extend_sign_halfword(immed))
		r[rt] = 1;
	else
		r[rt] = 0;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::SLTIU(int rt, int rs, int immed)
{
	PRINT_PC("SLTIU " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	if (r[rs] < extend_sign_halfword(immed))
		r[rt] = 1;
	else
		r[rt] = 0;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::SLTU(int rd, int rs, int rt)
{
	PRINT_PC("SLTU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	if (r[rs] < r[rt])
		r[rd] = 1;
	else
		r[rd] = 0;
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SRA(int rd, int rt, int sa)
{
	PRINT_PC("SRA " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word((sword) r[rt] >> sa);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SRAV(int rd, int rt, int rs)
{
	PRINT_PC("SRAV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((sword) r[rt] >> (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SRL(int rd, int rt, int sa)
{
	PRINT_PC("SRL " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << sa);
	r[rd] = extend_sign_word((word) r[rt] >> sa);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SRLV(int rd, int rt, int rs)
{
	PRINT_PC("SRLV " << dec << "r" << rd << " " << dec << "r" << rt << " " << dec << "r" << rs);
	r[rd] = extend_sign_word((word) r[rt] >> (r[rs]&0x1F));
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SUB(int rd, int rs, int rt)
{
#	if defined DEBUG
		if (!rs) { PRINT_PC("NEG " << dec << "r" << rd << " " << dec << "r" << rt); }
		else PRINT_PC("SUB " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif
	r[rd] = extend_sign_word(r[rs] - r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::SUBU(int rd, int rs, int rt)
{
#	if defined DEBUG
		if (!rs) { PRINT_PC("NEGU " << dec << "r" << rd << " " << dec << "r" << rt); }
		else PRINT_PC("SUBU " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
#	endif

	r[rd] = extend_sign_word(r[rs] - r[rt]);
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);

	pc += 4;
}

void R4300i::XOR(int rd, int rs, int rt)
{
	PRINT_PC("XOR " << dec << "r" << rd << " " << dec << "r" << rs << " " << dec << "r" << rt);
	r[rd] = r[rs] ^ r[rt];
	PRINT(" r" << dec << rd << hex << "=0x" << r[rd]);
	pc += 4;
}

void R4300i::XORI(int rt, int rs, int immed)
{
	PRINT_PC("XORI " << dec << "r" << rt << " " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	r[rt] = r[rs] ^ immed;
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::BEQ(int rs, int rt, int immed)
{
#	if defined DEBUG
		if (!rt && !rs) { PRINT_PC("B"); }
		else if (!rt) { PRINT_PC("BEQZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
		else PRINT_PC("BEQ " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif
	sdword local_rs = r[rs];
	sdword local_rt = r[rt];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs == local_rt)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BEQL(int rs, int rt, int immed)
{
#	if defined DEBUG
		if (!rt) { PRINT_PC("BEQLZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
		else PRINT_PC("BEQL " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	sdword local_rs = r[rs];
	sdword local_rt = r[rt];
	if (local_rs == local_rt)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BGEZ(int immed, int rs)
{
	PRINT_PC("BGEZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs >= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BGEZAL(int immed, int rs)
{
#	if defined DEBUG
		if (!rs) { PRINT_PC("BAL"); }
		else PRINT_PC("BGEZAL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	r[31] = pc;
	if (local_rs >= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BGEZALL(int immed, int rs)
{
	PRINT_PC("BGEZALL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs >= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		r[31] = pc;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BGEZL(int immed, int rs)
{
	PRINT_PC("BGEZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs >= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BGTZ(int rs, int immed)
{
	PRINT_PC("BGTZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs > 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BGTZL(int immed, int rs)
{
	PRINT_PC("BGTZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs > 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BLEZ(int rs, int immed)
{
	PRINT_PC("BLEZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs <= 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BLEZL(int immed, int rs)
{
	PRINT_PC("BLEZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs <= 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BLTZ(int immed, int rs)
{
	PRINT_PC("BLTZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs < 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BLTZAL(int immed, int rs)
{
	PRINT_PC("BLTZAL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	r[31] = pc;
	if (local_rs < 0)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BLTZALL(int immed, int rs)
{
	PRINT_PC("BLTZALL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs < 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		r[31] = pc;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BLTZL(int immed, int rs)
{
	PRINT_PC("BLTZL " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));

	sdword local_rs = r[rs];
	if (local_rs < 0)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::BNE(int rs, int rt, int immed)
{
#	if defined DEBUG
		if (!rt) { PRINT_PC("BNEZ " << dec << "r" << rs << " 0x" << hex << extend_sign_halfword(immed)); }
		else PRINT_PC("BNE " << dec << "r" << rs << " " << dec << "r" << rt << " 0x" << hex << extend_sign_halfword(immed));
#	endif

	dword local_rs = r[rs];
	dword local_rt = r[rt];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if (local_rs != local_rt)
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
}

void R4300i::BNEL(int rs, int rt, int immed)
{
#	if defined DEBUG
		if (!rt) { PRINT_PC("BNELZ " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed)); }
		else PRINT_PC("BNEL " << dec << "r" << rs << " " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed));
#	endif

	dword local_rs = r[rs];
	dword local_rt = r[rt];
	if (local_rs != local_rt)
	{
		pc += 4;
		delay_slot = true;
		decode(memory->read<word>(pc));
		++Count;
		delay_slot = false;
		pc += (extend_sign_halfword(extend_sign_halfword(immed) - 1) << 2);
	}
	else
		pc += 8;
}

void R4300i::J(int address)
{
	PRINT_PC("J " << address);

	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	pc = (pc & 0xF0000000) | ((address & 0x03FFFFFF) << 2);
}

void R4300i::JAL(int address)
{
	PRINT_PC("JAL " << address);
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	r[31] = extend_sign_word(pc);
	pc = (pc & 0xF0000000) | ((address & 0x03FFFFFF) << 2);
}

void R4300i::JALR(int rs, int rd)
{
	PRINT_PC("JALR " << dec << "r" << rs << " " << dec << "r" << rd);

	dword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	r[rd] = extend_sign_word(pc);
	pc = local_rs;
}

void R4300i::JR(int rs)
{
	PRINT_PC("JR " << dec << "r" << rs);

	dword local_rs = r[rs];
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	pc = local_rs;
}

void R4300i::BREAK(int immed)
{
	PRINT_PC("SYSCALL " << extend_sign_halfword(immed));
	trigger_break_exception();
}

void R4300i::SYSCALL(int immed)
{
	PRINT_PC("SYSCALL " << hex << "0x" << extend_sign_halfword(immed));
	trigger_syscall_exception();
}

void R4300i::TEQ(int rs, int rt)
{
	PRINT_PC("TEQ " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TEQI(int rs, int immed)
{
	PRINT_PC("TEQI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::TGE(int rs, int rt)
{
	PRINT_PC("TGE " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TGEI(int rs, int immed)
{
	PRINT_PC("TGEI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::TGEIU(int rs, int immed)
{
	PRINT_PC("TGEIU " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::TGEU(int rs, int rt)
{
	PRINT_PC("TGEU " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TLT(int rs, int rt)
{
	PRINT_PC("TLT " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TLTI(int rs, int immed)
{
	PRINT_PC("TLTI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::TLTIU(int rs, int immed)
{
	PRINT_PC("TLTIU " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::TLTU(int rs, int rt)
{
	PRINT_PC("TLTU " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TNE(int rs, int rt)
{
	PRINT_PC("TNE " << dec << "r" << rs << " " << dec << "r" << rt);
	pc += 4;
}

void R4300i::TNEI(int rs, int immed)
{
	PRINT_PC("TNEI " << dec << "r" << rs << " " << hex << "0x" << extend_sign_halfword(immed));
	pc += 4;
}

void R4300i::CACHE(int rt, int immed, int rs)
{
	PRINT_PC("CACHE " << dec << "r" << rt << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	pc += 4;
}

int jump_marker = 0;

void R4300i::ERET(void)
{
	++Count;
	PRINT_PC("ERET");
	if (Status & 0x4)
	{
	PRINT_PC(" : ERROR IN ERET");
	}
	else
	{
		Status &= 0xFFFFFFFD;
		pc = EPC;
	}
	ll = 0;
//	check_interupt();
}

void R4300i::MFC0(int rt, int fs)
{
	PRINT_PC("MFC0 " << dec << "r" << rt << " " << dec << "cop0" << fs);
	r[rt] = extend_sign_word(cop0[fs]);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::MTC0(int rt, int fs)
{
	PRINT_PC("MTC0 " << dec << "r" << rt << " " << dec << "cop0" << fs);

	switch(fs)
	{
	case 0:    // Index
		Index = r[rt] & 0x8000003F;
		if ((Index & 0x3F) > 31) 
			cout << print_addr((word) pc) << " il y a plus de 32 TLB";
		break;
	case 1:    // Random
		break;
	case 2:    // EntryLo0
		EntryLo0 = r[rt] & 0x3FFFFFFF;
		break;
	case 3:    // EntryLo1
		EntryLo1 = r[rt] & 0x3FFFFFFF;
		break;
	case 4:    // Context
		Context = (r[rt] & 0xFF800000) | (Context & 0x007FFFF0);
		break;
	case 5:    // PageMask
		PageMask = r[rt] & 0x01FFE000;
		break;
	case 6:    // Wired
		Wired = r[rt] & 0xFFFFFFFF;
		Random = 31;
		break;
	case 8:    // BadVAddr
		break;
	case 9:    // Count
		++Count;
		
			
		Count = r[rt] & 0xFFFFFFFF;
		break;
	case 10:   // EntryHi
		EntryHi = r[rt] & 0xFFFFE0FF;
		break;
	case 11:   // Compare
		//remove_event(COMPARE_INT);
		//add_interupt_event_count(COMPARE_INT, (unsigned long)rrt);
		Compare = r[rt] & 0xFFFFFFFF;
		Cause = Cause & 0xFFFFFFFFFFFF7FFF; //Timer interupt is clear
		break;
	case 12:   // Status
		Status = r[rt] & 0xFFFFFFFF;
		++Count;
//		check_interupt();
		break;
	case 13:   // Cause
		if (r[rt] != 0)
			cout << print_addr((word) pc) << " �criture dans Cause";
		else Cause = r[rt] & 0xFFFFFFFF;
		break;
	case 14:   // EPC
		EPC = r[rt] & 0xFFFFFFFF;
		break;
	case 15:  // PRevID
		break;
	case 16:  // Config
		Config = r[rt] & 0xFFFFFFFF;
		break;
	case 18:  // WatchLo
		WatchLo = r[rt] & 0xFFFFFFFF;
		break;
	case 19:  // WatchHi
		WatchHi = r[rt] & 0xFFFFFFFF;
		break;
	case 27: // CacheErr
		break;
	case 28: // TagLo
		TagLo = r[rt] & 0x0FFFFFC0;
		break;
	case 29: // TagHi
		TagHi = 0;
		break;
	default:
		cout << endl << "Unknown mtc0 write";
	}
	pc += 4;
}

void R4300i::TLBP(void)
{
	PRINT_PC("TLBP");
//	int i;
	Index = 0x80000000;
	/*  for (i = 0; i < 32; i++)
	{
	if (((tlb_e[i].vpn2 & (~tlb_e[i].mask)) ==
	(((EntryHi & 0xFFFFE000) >> 13) & (~tlb_e[i].mask))) &&
	((tlb_e[i].g) ||
	(tlb_e[i].asid == (EntryHi & 0xFF))))
	{
	cout << hex << "vpn2 " << tlb_e[i].vpn2 << " ~mask " << (~tlb_e[i].mask) << " EntryHi " << ((EntryHi & 0xFFFFE000) >> 13) << " g " << (tlb_e[i].g) << " asid " << tlb_e[i].asid << endl;
	Index = i;
	break;
	}
	}*/
	pc += 4;
}

void R4300i::TLBR(void)
{  
	PRINT_PC("TLBR");
	int index;
	index = Index & 0x1F;
	PageMask = tlb_e[index].mask << 13;
	EntryHi = ((tlb_e[index].vpn2 << 13) | tlb_e[index].asid);
	EntryLo0 = (tlb_e[index].pfn_even << 6) | (tlb_e[index].c_even << 3)
		| (tlb_e[index].d_even << 2) | (tlb_e[index].v_even << 1)
		| tlb_e[index].g;
	EntryLo1 = (tlb_e[index].pfn_odd << 6) | (tlb_e[index].c_odd << 3)
		| (tlb_e[index].d_odd << 2) | (tlb_e[index].v_odd << 1)
		| tlb_e[index].g;
	pc += 4;
}

void R4300i::TLBWI(void)
{
	PRINT_PC("TLBWI");
	unsigned int i;
	if (tlb_e[Index&0x3F].v_even)
	{
		for (i=tlb_e[Index&0x3F].start_even; i<tlb_e[Index&0x3F].end_even; i++)
		{
			tlb_lut_r[i>>12] = 0;
			invalid_code[i>>12] = 1;
		}
		if (tlb_e[Index&0x3F].d_even)
			for (i=tlb_e[Index&0x3F].start_even; i<tlb_e[Index&0x3F].end_even; i++)
				tlb_lut_w[i>>12] = 0;
	}
	if (tlb_e[Index&0x3F].v_odd)
	{
		for (i=tlb_e[Index&0x3F].start_odd; i<tlb_e[Index&0x3F].end_odd; i++)
		{
			tlb_lut_r[i>>12] = 0;
			invalid_code[i>>12] = 1;
		}
		if (tlb_e[Index&0x3F].d_odd)
			for (i=tlb_e[Index&0x3F].start_odd; i<tlb_e[Index&0x3F].end_odd; i++)
				tlb_lut_w[i>>12] = 0;
	}
	tlb_e[Index&0x3F].g = (EntryLo0 & EntryLo1 & 1);
	tlb_e[Index&0x3F].pfn_even = (EntryLo0 & 0x3FFFFFC0) >> 6;
	tlb_e[Index&0x3F].pfn_odd = (EntryLo1 & 0x3FFFFFC0) >> 6;
	tlb_e[Index&0x3F].c_even = (EntryLo0 & 0x38) >> 3;
	tlb_e[Index&0x3F].c_odd = (EntryLo1 & 0x38) >> 3;
	tlb_e[Index&0x3F].d_even = (EntryLo0 & 0x4) >> 2;
	tlb_e[Index&0x3F].d_odd = (EntryLo1 & 0x4) >> 2;
	tlb_e[Index&0x3F].v_even = (EntryLo0 & 0x2) >> 1;
	tlb_e[Index&0x3F].v_odd = (EntryLo1 & 0x2) >> 1;
	tlb_e[Index&0x3F].asid = (EntryHi & 0xFF);
	tlb_e[Index&0x3F].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
	tlb_e[Index&0x3F].r = (EntryHi & 0xC000000000000000LL) >> 62;
	tlb_e[Index&0x3F].mask = (PageMask & 0x1FFE000) >> 13;

	tlb_e[Index&0x3F].start_even = tlb_e[Index&0x3F].vpn2 << 13;
	tlb_e[Index&0x3F].end_even = tlb_e[Index&0x3F].start_even+
		(tlb_e[Index&0x3F].mask << 12) + 0xFFF;
	tlb_e[Index&0x3F].phys_even = tlb_e[Index&0x3F].pfn_even << 12;

	if (tlb_e[Index&0x3F].v_even)
	{
		if (tlb_e[Index&0x3F].start_even < tlb_e[Index&0x3F].end_even &&
			!(tlb_e[Index&0x3F].start_even >= 0x80000000 &&
			tlb_e[Index&0x3F].end_even < 0xC0000000) &&
			tlb_e[Index&0x3F].phys_even < 0x20000000)
		{
			for (i=tlb_e[Index&0x3F].start_even;i<tlb_e[Index&0x3F].end_even;i++)
				tlb_lut_r[i>>12] = 0x80000000 | 
				(tlb_e[Index&0x3F].phys_even + (i - tlb_e[Index&0x3F].start_even));
			if (tlb_e[Index&0x3F].d_even)
				for (i=tlb_e[Index&0x3F].start_even;i<tlb_e[Index&0x3F].end_even;i++)
					tlb_lut_w[i>>12] = 0x80000000 | 
					(tlb_e[Index&0x3F].phys_even + (i - tlb_e[Index&0x3F].start_even));
		}
	}
	tlb_e[Index&0x3F].start_odd = tlb_e[Index&0x3F].end_even+1;
	tlb_e[Index&0x3F].end_odd = tlb_e[Index&0x3F].start_odd+
		(tlb_e[Index&0x3F].mask << 12) + 0xFFF;
	tlb_e[Index&0x3F].phys_odd = tlb_e[Index&0x3F].pfn_odd << 12;

	if (tlb_e[Index&0x3F].v_odd)
	{
		if (tlb_e[Index&0x3F].start_odd < tlb_e[Index&0x3F].end_odd &&
			!(tlb_e[Index&0x3F].start_odd >= 0x80000000 &&
			tlb_e[Index&0x3F].end_odd < 0xC0000000) &&
			tlb_e[Index&0x3F].phys_odd < 0x20000000)
		{
			for (i=tlb_e[Index&0x3F].start_odd;i<tlb_e[Index&0x3F].end_odd;i++)
				tlb_lut_r[i>>12] = 0x80000000 | 
				(tlb_e[Index&0x3F].phys_odd + (i - tlb_e[Index&0x3F].start_odd));
			if (tlb_e[Index&0x3F].d_odd)
				for (i=tlb_e[Index&0x3F].start_odd;i<tlb_e[Index&0x3F].end_odd;i++)
					tlb_lut_w[i>>12] = 0x80000000 | 
					(tlb_e[Index&0x3F].phys_odd + (i - tlb_e[Index&0x3F].start_odd));
		}
	}
	pc += 4;
}

void R4300i::TLBWR(void)
{
	PRINT_PC("TLBWR");
	unsigned int i;
	++Count;
	Random = (Count/2 % (32 - Wired)) + Wired;
	if (tlb_e[Random].v_even)
	{
		for (i=tlb_e[Random].start_even; i<tlb_e[Random].end_even; i++)
		{
			tlb_lut_r[i>>12] = 0;
			invalid_code[i>>12] = 1;
		}
		if (tlb_e[Random].d_even)
			for (i=tlb_e[Random].start_even; i<tlb_e[Random].end_even; i++)
				tlb_lut_w[i>>12] = 0;
	}
	if (tlb_e[Random].v_odd)
	{
		for (i=tlb_e[Random].start_odd; i<tlb_e[Random].end_odd; i++)
		{
			tlb_lut_r[i>>12] = 0;
			invalid_code[i>>12] = 1;
		}
		if (tlb_e[Random].d_odd)
			for (i=tlb_e[Random].start_odd; i<tlb_e[Random].end_odd; i++)
				tlb_lut_w[i>>12] = 0;
	}
	tlb_e[Random].g = (EntryLo0 & EntryLo1 & 1);
	tlb_e[Random].pfn_even = (EntryLo0 & 0x3FFFFFC0) >> 6;
	tlb_e[Random].pfn_odd = (EntryLo1 & 0x3FFFFFC0) >> 6;
	tlb_e[Random].c_even = (EntryLo0 & 0x38) >> 3;
	tlb_e[Random].c_odd = (EntryLo1 & 0x38) >> 3;
	tlb_e[Random].d_even = (EntryLo0 & 0x4) >> 2;
	tlb_e[Random].d_odd = (EntryLo1 & 0x4) >> 2;
	tlb_e[Random].v_even = (EntryLo0 & 0x2) >> 1;
	tlb_e[Random].v_odd = (EntryLo1 & 0x2) >> 1;
	tlb_e[Random].asid = (EntryHi & 0xFF);
	tlb_e[Random].vpn2 = (EntryHi & 0xFFFFE000) >> 13;
	tlb_e[Random].r = (EntryHi & 0xC000000000000000LL) >> 62;
	tlb_e[Random].mask = (PageMask & 0x1FFE000) >> 13;

	tlb_e[Random].start_even = tlb_e[Random].vpn2 << 13;
	tlb_e[Random].end_even = tlb_e[Random].start_even+
		(tlb_e[Random].mask << 12) + 0xFFF;
	tlb_e[Random].phys_even = tlb_e[Random].pfn_even << 12;

	if (tlb_e[Random].v_even)
	{
		if (tlb_e[Random].start_even < tlb_e[Random].end_even &&
			!(tlb_e[Random].start_even >= 0x80000000 &&
			tlb_e[Random].end_even < 0xC0000000) &&
			tlb_e[Random].phys_even < 0x20000000)
		{
			for (i=tlb_e[Random].start_even;i<tlb_e[Random].end_even;i++)
				tlb_lut_r[i>>12] = 0x80000000 | 
				(tlb_e[Random].phys_even + (i - tlb_e[Random].start_even));
			if (tlb_e[Random].d_even)
				for (i=tlb_e[Random].start_even;i<tlb_e[Random].end_even;i++)
					tlb_lut_w[i>>12] = 0x80000000 | 
					(tlb_e[Random].phys_even + (i - tlb_e[Random].start_even));
		}
	}
	tlb_e[Random].start_odd = tlb_e[Random].end_even+1;
	tlb_e[Random].end_odd = tlb_e[Random].start_odd+
		(tlb_e[Random].mask << 12) + 0xFFF;
	tlb_e[Random].phys_odd = tlb_e[Random].pfn_odd << 12;

	if (tlb_e[Random].v_odd)
	{
		if (tlb_e[Random].start_odd < tlb_e[Random].end_odd &&
			!(tlb_e[Random].start_odd >= 0x80000000 &&
			tlb_e[Random].end_odd < 0xC0000000) &&
			tlb_e[Random].phys_odd < 0x20000000)
		{
			for (i=tlb_e[Random].start_odd;i<tlb_e[Random].end_odd;i++)
				tlb_lut_r[i>>12] = 0x80000000 | 
				(tlb_e[Random].phys_odd + (i - tlb_e[Random].start_odd));
			if (tlb_e[Random].d_odd)
				for (i=tlb_e[Random].start_odd;i<tlb_e[Random].end_odd;i++)
					tlb_lut_w[i>>12] = 0x80000000 | 
					(tlb_e[Random].phys_odd + (i - tlb_e[Random].start_odd));
		}
	}
	pc += 4;
}

template<typename Type>
void R4300i::ABS(int fd, int fs)
{
	PRINT_PC("ABS " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) abs((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::ADD(int fd, int fs, int ft)
{
	PRINT_PC("ADD " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	f[fd] = (dword) ((Type) f[fs] + (Type) f[ft]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::BC1F(int immed)
{
	PRINT_PC("BC1F " << hex << "0x" << extend_sign_halfword(immed));
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = 1;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = 0;
	if ((fcr31 & 0x800000)==0)
		pc = pc_tmp;
	else
		pc += 4;
	
		
}

void R4300i::BC1FL(int immed)
{
	PRINT_PC("BC1FL " << hex << "0x" << extend_sign_halfword(immed));
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if ((fcr31 & 0x800000)==0)
		pc = pc_tmp;
	else
		pc += 4;
	
		
}

void R4300i::BC1T(int immed)
{
	PRINT_PC("BC1T " << hex << "0x" << extend_sign_halfword(immed));
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = 1;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = 0;
	if ((fcr31 & 0x800000)!=0)
		pc = pc_tmp;
	else
		pc += 4;
	
		
}

void R4300i::BC1TL(int immed)
{
	PRINT_PC("BC1TL " << hex << "0x" << extend_sign_halfword(immed));
	dword pc_tmp = pc + extend_sign_halfword(immed);
	pc += 4;
	delay_slot = true;
	decode(memory->read<word>(pc));
	++Count;
	delay_slot = false;
	if ((fcr31 & 0x800000) != 0)
		pc = pc_tmp;
	else
		pc += 4;
}

template<typename Type>
void R4300i::C(int fs, int ft, int cond)
{
	PRINT_PC("C " << dec << "f" << fs << " " << dec << "f" << ft << " " << dec << "cond " << cond);
	switch (cond) {
	case 0:
		F<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 1:
		UN<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 2:
		EQ<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 3:
		UEQ<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 4:
		OLT<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 5:
		ULT<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 6:
		OLE<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 7:
		ULE<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 8:
		SF<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 9:
		NGLE<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 10:
		SEQ<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 11:
		NGL<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 12:
		LT<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 13:
		NGE<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 14:
		LE<Type>((Type) f[fs], (Type) f[ft]);
		break;
	case 15:
		NGT<Type>((Type) f[fs], (Type) f[ft]);
		break;
	default:
		cout << endl << "Unknown Condition";
		break;
	}
	pc += 4;
}

template<typename Type, typename toType>
void R4300i::CEIL(int fd, int fs)
{
	PRINT_PC("CEIL " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (toType) ((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::CFC1(int rt, int fs)
{
	PRINT_PC("CFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	if (fs == 0)
		r[rt] = extend_sign_word(fcr0);
	else
		r[rt] = extend_sign_word(fcr31);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::CTC1(int rt, int fs)
{
	PRINT_PC("CTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	if (fs == 0)
		fcr0 = r[rt] & 0xFFFFFFFF;
	else
		fcr31 = r[rt] & 0xFFFFFFFF;
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<typename Type, typename toType>
void R4300i::CVT(int fd, int fs)
{
	PRINT_PC("CVT " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) ((toType) ((Type) f[fs]));
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::DIV(int fd, int fs, int ft)
{
	PRINT_PC("DIV " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	f[fd] = (dword) ((Type) f[fs] / (Type) f[ft]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::DMFC1(int rt, int fs)
{
	PRINT_PC("DMFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	r[rt] = f[fs];
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

void R4300i::DMTC1(int rt, int fs)
{
	PRINT_PC("DMTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	f[fs] = r[rt];
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<typename Type, typename toType>
void R4300i::FLOOR(int fd, int fs)
{
	PRINT_PC("FLOOR " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (toType) ((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::LDC1(int ft, int immed, int rs)
{
	PRINT_PC("LDC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	f[ft] = memory->read<dword>(r[rs] + extend_sign_halfword(immed) * sizeof(dword));
	PRINT_PC(" f" << dec << ft << hex << "=0x" << f[ft]);
	pc += 4;
}

void R4300i::LWC1(int ft, int immed, int rs)
{
	PRINT_PC("LWC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	f[ft] = memory->read<word>(r[rs] + extend_sign_halfword(immed));
	PRINT_PC(" f" << dec << ft << hex << "=0x" << f[ft]);
	pc += 4;
}

void R4300i::MFC1(int rt, int fs)
{
	PRINT_PC("MFC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	r[rt] = extend_sign_word(f[fs]);
	PRINT(" r" << dec << rt << hex << "=0x" << r[rt]);
	pc += 4;
}

template<typename Type>
void R4300i::MOV(int fd, int fs)
{
	PRINT_PC("MOV " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) ((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::MTC1(int rt, int fs)
{
	PRINT_PC("MTC1 " << dec << "r" << rt << " " << dec << "f" << fs);
	f[fs] = r[rt] & 0xFFFFFFFF;
	PRINT_PC(" f" << dec << fs << hex << "=0x" << f[fs]);
	pc += 4;
}

template<typename Type>
void R4300i::MUL(int fd, int fs, int ft)
{
	PRINT_PC("MUL " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	f[fd] = (dword) ((Type) f[fs] * (Type) f[ft]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::NEG(int fd, int fs)
{
	PRINT_PC("NEG " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) (- (Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type, typename toType>
void R4300i::ROUND(int fd, int fs)
{
	PRINT_PC("ROUND " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (toType) ((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::SDC1(int ft, int immed, int rs)
{
	PRINT_PC("SDC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	memory->write<dword>(f[ft], r[rs] + extend_sign_halfword(immed) * sizeof(dword));
	pc += 4;
}

template<>
void R4300i::SQRT<w>(int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) sqrt((double)f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<>
void R4300i::SQRT<l>(int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) sqrt((double)f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::SQRT(int fd, int fs)
{
	PRINT_PC("SQRT " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (dword) sqrt((Type)f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::SUB(int fd, int fs, int ft)
{
	PRINT_PC("SUB " << dec << "f" << fd << " " << dec << "f" << fs << " " << dec << "f" << ft);
	f[fd] = (dword) ((Type) f[fs] - (Type) f[ft]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

void R4300i::SWC1(int ft, int immed, int rs)
{
	PRINT_PC("SWC1 " << dec << "f" << ft << " " << hex << "0x" << extend_sign_halfword(immed) << " " << dec << "r" << rs);
	memory->write<word>((word) f[ft], (r[rs] + extend_sign_halfword(immed) & 0xFFFFFFFF));
	pc += 4;
}

template<typename Type, typename toType>
void R4300i::TRUNC(int fd, int fs)
{
	PRINT_PC("TRUNC " << dec << "f" << fd << " " << dec << "f" << fs);
	f[fd] = (toType) ((Type) f[fs]);
	PRINT_PC(" f" << dec << fd << hex << "=0x" << f[fd]);
	pc += 4;
}

template<typename Type>
void R4300i::F(Type a, Type b)
{
	fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::UN(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::EQ(Type a, Type b)
{
	if (!_isnan((double) a) && !_isnan((double) b) && a == b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::UEQ(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b) || a == b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::OLT(Type a, Type b)
{
	if (!_isnan((double) a) && !_isnan((double) b) && a < b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::ULT(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b) || a < b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::OLE(Type a, Type b)
{
	if (!_isnan((double) a) && !_isnan((double) b) && a <= b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::ULE(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b) || a <= b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::SF(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::NGLE(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	fcr31 &= ~0x800000;
}


template<typename Type>
void R4300i::SEQ(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a == b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::NGL(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a == b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::LT(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a < b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::NGE(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a < b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::LE(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a <= b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}

template<typename Type>
void R4300i::NGT(Type a, Type b)
{
	if (_isnan((double) a) || _isnan((double) b))
	{
		cout << print_addr((word) pc) << " Invalid operation exception in C opcode";
	}
	if (a <= b)
		fcr31 |= 0x800000;
	else
		fcr31 &= ~0x800000;
}