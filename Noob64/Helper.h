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

// Format a number
string format_number(string s, char c, int frequency);

// Prints an address in the standard representation
string print_addr(word address);

// Returns the word contained at the address pointed by ptr
byte getByte(char **ptr);

// Prints the memory contained in the array data
void dump_array(word start_addr, const byte *data, unsigned int size, int type);

// Converts a byte array to its type representation
template <typename Type> inline Type binary_to_type(const byte *address);

// Converts a type to its binary representation
template <typename Type> inline Type type_to_binary(Type data);

void dummy();