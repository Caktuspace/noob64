#pragma once

class RomLoader
{
public:
	RomLoader(void);
	RomLoader(char* filename);
	word* getBootCode(void);
private:
	byte		PI_BSB_DOM1_LAT_REG;
	byte		PI_BSB_DOM1_PGS_REG;
	byte		PI_BSB_DOM1_PWD_REG;
	byte		PI_BSB_DOM1_PGS_2_REG;
	word		clock;
	word		pc;
	word		release;
	word		CRC1;
	word		CRC2;
	char		name[20];
	word		manufacturer;
	hword		cartridge;
	hword		country;
	word		bootcode[BOOT_CODE_SIZE];
};

