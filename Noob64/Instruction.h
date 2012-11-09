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

#pragma once

//extend the negative bit to a dword if 1 in word
inline dword extend_sign_word(dword d);

//extend the negative bit to a dword if 1 in halfword
inline dword extend_sign_halfword(dword d);

//extend the negative bit to a dword if 1 in byte
inline dword extend_sign_byte(dword d);

//getOpCode retreives the Op code from an instruction
inline int getOpCode(word instr);

//getRs retreives the source register from an instruction
inline int getRs(word instr);

//getRt retreives the target register from an instruction
inline int getRt(word instr);

//getRd retreives the destination register from an instruction
inline int getRd(word instr);

//getSa retreives the shift amount from an instruction
inline int getSa(word instr);

//getFunct retreives the function from the instruction
inline int getFunct(word instr);

//getImmediate retreives the immediate from the instruction
inline int getImmediate(word instr);

//getTarget retreives the jump target address from the instruction
inline int getTarget(word instr);

//getCond retreives the jump condition from the instruction
inline int getCond(word instr);

//getNd retreives the nd from the instruction useful for the bc instruction
inline int getNd(word instr);

//getTf retreives the tf from the instruction useful for the bc instruction
inline int getTf(word instr);

//getNdTf retreives the nd and tf from the instruction useful for the bc instruction
inline int getNdTf(word instr);
