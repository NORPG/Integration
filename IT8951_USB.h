#ifndef IT8951_USB_H

#define IT8951_USB_H

#include "IT8951_CMD.h"

#ifndef Include_Main

#define Include_Main

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#define _Test_SW_

void show_sense_buffer(SG_IO_HDR *);

void IT8951_Cmd_Inquiry(void);
void IT8951_Cmd_SysInfo(SystemInfo *);
void IT8951_Cmd_MemRead(DWord, Word, Byte *);
void IT8951_Cmd_MemWrite(DWord, Word, Byte *);
void IT8951_Cmd_RegRead(DWord, DWord *);
void IT8951_Cmd_RegWrite(DWord, DWord *);
void IT8951_Cmd_DisplayArea(DWord, DWord, DWord, DWord, DWord, DWord,
			    DWord);
void IT8951_Cmd_LoadImageArea(Byte *, DWord, DWord, DWord, DWord, DWord);
void IT8951_Cmd_SetTemp(TempArg);
void dis_num(SystemInfo * Sys_info, Byte * src, int num, int x, int y);
#endif
