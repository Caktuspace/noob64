#include "StdAfx.h"
#include "R4300i.h"

R4300i::R4300i(void)
{
}

void R4300i::decode(const word instr)
{
	switch(getOpCode(instr)) {

	case 0: // 000000
		decode_r(instr);
		break;
	case 1: // 
		break;
	case 2: // 
		break;
	case 3: // 
		break;
	case 4: // 
		break;
	case 5: // 
		break;
	case 6: // 
		break;
	case 7: // 
		break;
	case 8: // 001000
		ADDI(getRt(instr), getRs(instr), getImmed(instr));
		break;
	case 9: // 
		break;
	case 10: // 
		break;
	case 11: // 
		break;
	case 12: // 
		break;
	case 13: // 
		break;
	case 14: // 
		break;
	case 15: // 
		break;
	case 16: // 
		break;
	case 17: // 
		break;
	case 18: // 
		break;
	case 19: // 
		break;
	case 20: // 
		break;
	case 21: // 
		break;
	case 22: // 
		break;
	case 23: // 
		break;
	case 24: // 
		break;
	case 25: // 
		break;
	case 26: // 
		break;
	case 27: // 
		break;
	case 28: // 
		break;
	case 29: // 
		break;
	case 30: // 
		break;
	case 31: // 
		break;
	case 32: // 
		break;
	case 33: // 
		break;
	case 34: // 
		break;
	case 35: // 
		break;
	case 36: // 
		break;
	case 37: // 
		break;
	case 38: // 
		break;
	case 39: // 
		break;
	case 40: // 
		break;
	case 41: // 
		break;
	case 42: // 
		break;
	case 43: // 
		break;
	case 44: // 
		break;
	case 45: // 
		break;
	case 46: // 
		break;
	case 47: // 
		break;
	case 48: // 
		break;
	case 49: // 
		break;
	case 50: // 
		break;
	case 51: // 
		break;
	case 52: // 
		break;
	case 53: // 
		break;
	case 54: // 
		break;
	case 55: // 
		break;
	case 56: // 
		break;
	case 57: // 
		break;
	case 58: // 
		break;
	case 59: // 
		break;
	case 60: // 
		break;
	case 61: // 
		break;
	case 62: // 
		break;
	case 63: // 
		break;

	default: // Unknown instruction
		char mem[64];
		itoa(instr, mem, 2);
		cerr << "	Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
		exit(0);
	}
}

inline void R4300i::decode_r(word instr)
{
//	switch(instr.getFunc()) {
//	case 0: // 0b000000
////		SLL
//		break;
//
//	default: /* Unknown instruction */
//		char mem[64];
//		itoa(instr.getInstr(), mem, 2);
//		cerr << "	Unknown instruction: " << format_number(string(32 - strlen(mem), '0') + mem, ' ', 4) << endl;
//		exit(0);
//	}
}

void R4300i::ADDI(int rt, int rs, int immed)
{
	r[rt] = r[rs] + immed;
    //FIXME: If overflow occurs, then trap.
}