#include "IT8951_USB.h"
#include <math.h>
#include <stdio.h>

extern int evpd;
extern char *path;
extern int page_code;
extern int gulPanelW;
extern int gulPanelH;
extern unsigned char sense_buffer[SENSE_LEN];
extern unsigned char data_buffer[BLOCK_LEN * 256];

void dis_num(SystemInfo * Sys_info, Byte * src, char ch, int x, int y)
{
    switch (ch) {
    case '0':
	memset((src), 0x00, (4 * 26));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 26);	//_

	memset((src), 0x00, (4 * 26));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 26);	//_

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 30, 4);	//|

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 32, 30, 4);	//|
	break;
    case '1':
	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10,
				 y + 23, 30, 4);
	break;
    case '2':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 10));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 10));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 15, 4);	//|

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 36, 15, 4);	//|
	break;
    case '3':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (19 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 36, 15, 4);	//|
	break;
    case '4':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (19 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 19, 4);	//|

	memset((src), 0x00, (3 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 34, 4);	//|
	break;
    case '5':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (19 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|
	break;
    case '6':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (34 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 34, 4);	//|

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|
	break;
    case '7':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

	memset((src), 0x00, (19 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 30, 4);	//|
	break;
    case '8':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 30, 4);	//|

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 30, 4);	//|
	break;
    case '9':
	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 26);	//_

	memset((src), 0x00, (4 * 30));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 26);	//-

	memset((src), 0x00, (15 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

	memset((src), 0x00, (30 * 4));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 32, 30, 4);	//|
	break;
    }
}

void show_sense_buffer(struct sg_io_hdr *hdr)
{
    unsigned char *buffer = hdr->sbp;

    for (int i = 0; i < hdr->mx_sb_len; ++i) {
	putchar(buffer[i]);
    }
}

void IT8951_Cmd_Inquiry(void)
{

    struct sg_io_hdr *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, data_buffer, BLOCK_LEN * 256);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Inquiry\n");

	status = IT8951_CMD_INQ(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    for (int i = 8; i < 36; i++) {
		printf("%c", data_buffer[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_SysInfo(SystemInfo * Sys_info)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, Sys_info, (sizeof(SystemInfo) / sizeof(DWord)));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Get device information\n");

	status = IT8951_CMD_SYSTEM_INFO(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    SystemInfo *temp = p_hdr->dxferp;

	    Sys_info->uiStandardCmdNo = SWAP_32(temp->uiStandardCmdNo);
	    Sys_info->uiExtendCmdNo = SWAP_32(temp->uiExtendCmdNo);
	    Sys_info->uiSignature = SWAP_32(temp->uiSignature);
	    Sys_info->uiVersion = SWAP_32(temp->uiVersion);
	    Sys_info->uiWidth = SWAP_32(temp->uiWidth);
	    Sys_info->uiHeight = SWAP_32(temp->uiHeight);
	    Sys_info->uiUpdateBufBase = SWAP_32(temp->uiUpdateBufBase);
	    Sys_info->uiImageBufBase = SWAP_32(temp->uiImageBufBase);
	    Sys_info->uiTemperatureNo = SWAP_32(temp->uiTemperatureNo);
	    Sys_info->uiModeNo = SWAP_32(temp->uiModeNo);

	    for (int i = 0; i < 8; i++) {
		Sys_info->uiFrameCount[i] = SWAP_32(temp->uiFrameCount[i]);
	    }

	    Sys_info->uiNumImgBuf = SWAP_32(temp->uiNumImgBuf);

	    Sys_info->uiWbfSFIAddr = SWAP_32(temp->uiWbfSFIAddr);

	    for (int i = 0; i < 9; i++) {
		Sys_info->uiReserved[i] = SWAP_32(temp->uiReserved[i]);
	    }

	    gulPanelW = Sys_info->uiWidth;
	    gulPanelH = Sys_info->uiHeight;

	    //#if defined(_TEST_SW_)
	    printf("Panel Width: %d\n", Sys_info->uiWidth);
	    printf("Panel Height: %d\n", Sys_info->uiHeight);
	    printf("Image buffer address: %X\n", Sys_info->uiImageBufBase);
	    printf("Update buffer address: %X\n",
		   Sys_info->uiUpdateBufBase);
	    //#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_MemRead(DWord memAddr, Word length, Byte * revBuf)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    //Byte *rev = (Byte*)malloc(sizeof(Byte)*length);

    set_xfer_data(p_hdr, revBuf, length);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Read memory\n");

	// Notice that the memAddr should be 0x format
	status =
	    IT8951_CMD_READ_MEM(fd, page_code, evpd, p_hdr, memAddr,
				length);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_Test_SW_)
	    printf("Read memory 0x%X: \r\n", memAddr);
	    for (int i = 0; i < length; i++) {
		printf("%X \r", revBuf[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_MemWrite(DWord memAddr, Word length, Byte * srcBuf)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, srcBuf, length);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Write memory\n");

	status =
	    IT8951_CMD_WRITE_MEM(fd, page_code, evpd, p_hdr, memAddr,
				 length);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    printf("Write memory 0x%X: \r\n", memAddr);

	    for (int i = 0; i < length; i++) {
		printf("%X \r", srcBuf[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_RegRead(DWord regAddr, DWord * rev)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, rev, sizeof(DWord));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Read register\n");

	status = IT8951_CMD_READ_REG(fd, page_code, evpd, p_hdr, regAddr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    *rev = SWAP_32(*rev);

#if defined(_Test_SW_)
	    printf("Read register 0x%X: \r\n", regAddr);
	    printf("%X \r", *rev);
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_RegWrite(DWord regAddr, DWord * src)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    DWord srcIn = SWAP_32(*src);

    set_xfer_data(p_hdr, &srcIn, sizeof(DWord));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Write register\n");

	status = IT8951_CMD_WRITE_REG(fd, page_code, evpd, p_hdr, regAddr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    printf("Write register 0x%X: \r\n", regAddr);
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void
IT8951_Cmd_DisplayArea(DWord dpyX, DWord dpyY, DWord dpyW, DWord dpyH,
		       DWord dpyMode, DWord memAddr, DWord enWaitRdy)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    DisplayArg displayArg;

    displayArg.iPosX = SWAP_32(dpyX);	//Conver Little to Big for IT8951/61
    displayArg.iPosY = SWAP_32(dpyY);
    displayArg.iWidth = SWAP_32(dpyW);
    displayArg.iHeight = SWAP_32(dpyH);
    displayArg.iEngineIndex = SWAP_32(enWaitRdy);
    displayArg.iMemAddr = SWAP_32(memAddr);
    displayArg.iWavMode = SWAP_32(dpyMode);

    set_xfer_data(p_hdr, &displayArg, sizeof(DisplayArg));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Display\n");

	status = IT8951_CMD_DPY_AREA(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    printf("Refreshing (%d, %d, %d, %d) with mode %d ... \r\n",
		   dpyX, dpyY, dpyW, dpyH, dpyMode);
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void
IT8951_Cmd_LoadImageArea(Byte * srcImg, DWord memAddr, DWord ldX,
			 DWord ldY, DWord ldW, DWord ldH)
{

    printf("\nCommand: Load image\n");

    if (ldW <= 2048 && ldW != gulPanelW) {
	SG_IO_HDR *p_hdr = init_io_hdr();

	//Using IT8951 New USB Command for Loading Image - it Needs IT8951 F/W support
	DWord counter = (SPT_BUF_SIZE / ldW);
	LoadArg loadArg;

	int status = 0;
	int fd = open(path, O_RDWR);

	for (DWord i = 0; i < ldH; i += counter) {
	    if (counter > (ldH - i)) {
		counter = (ldH - i);
	    }

	    Byte *tempBuf =
		(Byte *) malloc((sizeof(LoadArg) + (ldW * counter)));

	    loadArg.iX = SWAP_32(ldX);
	    loadArg.iY = SWAP_32((ldY + i));
	    loadArg.iW = SWAP_32(ldW);
	    loadArg.iH = SWAP_32(counter);

	    //Set Image Buffer Start Address
	    loadArg.iAddress = SWAP_32(memAddr);

	    memcpy(tempBuf, &loadArg, sizeof(LoadArg));
	    memcpy((tempBuf + sizeof(LoadArg)), (srcImg + (i * ldW)),
		   (ldW * counter));

	    set_xfer_data(p_hdr, tempBuf,
			  (sizeof(LoadArg) + (ldW * counter)));
	    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

	    if (fd > 0) {
		status = IT8951_CMD_LOAD_IMG(fd, page_code, evpd, p_hdr);
		if (status != 0) {
		    show_sense_buffer(p_hdr);
		} else {
		    // Show some information of loaded data?
		}
	    } else {
		printf("failed to open sg file %s\n", path);
	    }
	    free(tempBuf);
	}

	close(fd);
	destroy_io_hdr(p_hdr);
    } else {
	//Full Image - Fast Method => Send Multi Lines for each transfer
	DWord counter = (SPT_BUF_SIZE / ldW);

	for (DWord i = 0; i < ldH; i += counter) {
	    if (counter > (ldH - i)) {
		counter = (ldH - i);
	    }
	    //We Send Multi Lines for each Bulk Transfer
	    IT8951_Cmd_MemWrite((memAddr + ldX + ((ldY + i) * gulPanelW)),
				(Word) (ldW * counter),
				(srcImg + (i * ldW)));
	}
    }
}

void IT8951_Cmd_SetTemp(TempArg SetTemp)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    Byte flag = SetTemp.ucSetTemp;
    Byte value = SetTemp.ucTempVal;

    set_xfer_data(p_hdr, &SetTemp, sizeof(TempArg) / sizeof(Byte));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);
    char swap_temp = 0;

    if (fd > 0) {
	printf("\nCommand: Set temperature\n");

	status =
	    IT8951_CMD_SET_TEMP(fd, page_code, evpd, p_hdr,
				SetTemp.ucSetTemp, SetTemp.ucTempVal);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    if ((flag) == 0x00) {
		TempArg *temp = (p_hdr->dxferp);

		// will return a word , swap it because it8951 is big endian.
		swap_temp = temp->ucTempVal;
		temp->ucTempVal = temp->ucSetTemp;
		temp->ucSetTemp = swap_temp;
		printf("Get temperature: %X\n", temp->ucTempVal);
	    } else {
		printf("Set temperature, now forced as %d\n", value);
		printf("Please read temperature again to check it.\n");
	    }
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}
