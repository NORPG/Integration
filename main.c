#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "can.h"
#include "IT8951_USB.h"

#include <wiringPi.h>
#include <wiringSerial.h>

unsigned char sense_buffer[SENSE_LEN];
unsigned char data_buffer[BLOCK_LEN * 256];

DWord gulPanelW, gulPanelH;

char *path;
int evpd, page_code;

void dis_line(SystemInfo * Sys_info, Byte * src, unsigned char line,
	      char ch_buf[32][24]);
void test_num(SystemInfo * Sys_info, Byte * Src, char ch_buf[32][24]);

int main(int argc, char *argv[])
{
    char ch_buf[32][24] = { 0 };
    int s;

    char bms_buf[48] = { 0 };
    int bms_id = 0;
    int bms_flag = 1;
    /*
     * init can socket
     */
    s = create_socket("can0");
    if (s < 0) {
	printf("error: socket create fail");
	return -1;
    }

    int serial_bms, serial_adas;
    if ((serial_bms = serialOpen("/dev/ttyS0", 9600)) < 0) {	/* open serial port */
	fprintf(stderr, "Unable to open serial device: %s\n",
		strerror(errno));
	return 1;
    }

    if ((serial_adas = serialOpen("/dev/ttyUSB0", 9600)) < 0) {	/* open serial port */
	fprintf(stderr, "Unable to open serial device: %s\n",
		strerror(errno));
//	return 1;
    }


    if (wiringPiSetup() == -1) {	/* initializes wiringPi setup */
	fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
	return 1;
    }
    Byte src[(1600 * 1200)];

    SystemInfo *Sys_info;	// SystemInfo structure

    path = argv[1];		// arg1: sg path of device
    evpd = page_code = 0;

    printf("%d\n\r", argc);
    if (argc == 2) {
	/*
	 * 0x80: get system info
	 */
	Sys_info = (SystemInfo *) malloc(sizeof(SystemInfo));
	IT8951_Cmd_SysInfo(Sys_info);

	/* 
	 * set full white
	 */
	memset((src), 0xF0, (gulPanelW * gulPanelH));	//All white
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 0, 0,
				 gulPanelW, gulPanelH);
	IT8951_Cmd_DisplayArea(0, 0, gulPanelW, gulPanelH, 2,
			       (Sys_info->uiImageBufBase), 1);

	test_num(Sys_info, src, ch_buf);
    }

    {
	serialPutchar(serial_bms, 0xA5);
	serialPutchar(serial_bms, 0x5A);
	serialPutchar(serial_bms, 0x00);
	serialPutchar(serial_bms, 0x00);
	serialPutchar(serial_bms, 0x01);
    }

    {
	serialPutchar(serial_adas, 0x2E);
	serialPutchar(serial_adas, 0x01);
	serialPutchar(serial_adas, 0x02);
	serialPutchar(serial_adas, 0x40);
	serialPutchar(serial_adas, 0x00);
	serialPutchar(serial_adas, 0xBC);
    }

    delay(1);

    while (1) {
	struct can_frame *r_frame = calloc(1, sizeof(*r_frame));

	while (serialDataAvail(serial_bms) && (bms_flag == 1)) {
	    int dat = serialGetchar(serial_bms);	/* receive character serially */
	    if (dat != -1) {
		printf("%02X ", dat);	//Receive HEX
		fflush(stdout);
		bms_buf[bms_id] = dat;
		bms_id++;
		if (bms_id == 48)
		    bms_flag = 0;
	    }
	}
	while (serialDataAvail(serial_adas)) {
	    int dat = serialGetchar(serial_adas);	/* receive character serially */
	    if (dat != -1) {
		printf("%02X ", dat);	//Receive HEX
		fflush(stdout);
	    }
	}

	if (recv_can(s, r_frame) == 0) {
	    dump_can(r_frame);
	    if (r_frame->data[0] == 0x03) {
		if (r_frame->data[1] == 0x02) {

		    switch (r_frame->data[2]) {
		    case 0x10:
			sprintf(ch_buf[0], "%3d %2d %3d %2d",
				r_frame->data[3], r_frame->data[4],
				r_frame->data[5], r_frame->data[6]);
			dis_line(Sys_info, src, 0, ch_buf);
			break;
		    case 0x11:
			if (r_frame->data[3] < 4) {
			    int valx =
				(r_frame->data[4] << 8) + r_frame->data[5];
			    int valy =
				(r_frame->data[6] << 8) + r_frame->data[7];
			    sprintf(ch_buf[r_frame->data[3] + 1],
				    "%5d %5d", valx, valy);
			    dis_line(Sys_info, src, r_frame->data[3] + 1,
				     ch_buf);
			}
			break;
		    case 0x12:
			sprintf(ch_buf[5], "%1d", r_frame->data[3]);
			dis_line(Sys_info, src, 5, ch_buf);
			break;
		    case 0x13:{
			    int valx =
				(r_frame->data[3] << 4) + r_frame->data[4];
			    int valy =
				(r_frame->data[5] << 4) + r_frame->data[6];
			    sprintf(ch_buf[6], "%4d %4d %2x", valx, valy,
				    r_frame->data[7]);
			    dis_line(Sys_info, src, 6, ch_buf);
			    break;
			}
		    case 0x14:{
			    int vall =
				(r_frame->data[3] << 8) + r_frame->data[4];
			    int valr =
				(r_frame->data[5] << 8) + r_frame->data[6];
			    sprintf(ch_buf[r_frame->data[3] + 1],
				    "%5d %5d", vall, valr);
			    dis_line(Sys_info, src, 7, ch_buf);
			    break;
			}
		    case 0x15:
			switch (r_frame->data[3]) {
			case 0x00:
			    sprintf(ch_buf[8],
				    "%3d %3d %3d %3d", r_frame->data[4],
				    r_frame->data[5], r_frame->data[6],
				    r_frame->data[7]);
			    dis_line(Sys_info, src, 8, ch_buf);
			    break;
			case 0x01:
			    sprintf(ch_buf[9],
				    "%3d %3d", r_frame->data[4],
				    r_frame->data[5]);
			    dis_line(Sys_info, src, 9, ch_buf);
			    break;
			}
			break;
		    }
		    memset((src), 0xF0, (gulPanelW * gulPanelH));	//All white
		    IT8951_Cmd_LoadImageArea(src,
					     (Sys_info->uiImageBufBase),
					     0, 0, gulPanelW, gulPanelH);
		    /*
		     *      do something
		     */
		}
	    }
	}
	free(r_frame);

	if (bms_flag == 0) {
	    sprintf(ch_buf[10], "%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",
		    bms_buf[0], bms_buf[1], bms_buf[2], bms_buf[3],
		    bms_buf[4], bms_buf[5], bms_buf[6], bms_buf[7],
		    bms_buf[8], bms_buf[9], bms_buf[10], bms_buf[11]);
	    sprintf(ch_buf[11], "%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",
		    bms_buf[12], bms_buf[13], bms_buf[14], bms_buf[15],
		    bms_buf[16], bms_buf[17], bms_buf[18], bms_buf[19],
		    bms_buf[20], bms_buf[21], bms_buf[22], bms_buf[23]);
	    sprintf(ch_buf[12], "%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",
		    bms_buf[24], bms_buf[25], bms_buf[26], bms_buf[27],
		    bms_buf[28], bms_buf[29], bms_buf[30], bms_buf[31],
		    bms_buf[32], bms_buf[33], bms_buf[34], bms_buf[35]);
	    sprintf(ch_buf[13], "%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",
		    bms_buf[36], bms_buf[37], bms_buf[38], bms_buf[39],
		    bms_buf[40], bms_buf[41], bms_buf[42], bms_buf[43],
		    bms_buf[44], bms_buf[45], bms_buf[46], bms_buf[47]);
	    dis_line(Sys_info, src, 10, ch_buf);
	    dis_line(Sys_info, src, 11, ch_buf);
	    dis_line(Sys_info, src, 12, ch_buf);
	    dis_line(Sys_info, src, 13, ch_buf);
	    memset((src), 0xF0, (gulPanelW * gulPanelH));	//All white
	    IT8951_Cmd_LoadImageArea(src,
				     (Sys_info->uiImageBufBase),
				     0, 0, gulPanelW, gulPanelH);
	}

	sleep(1);
    }

    free(Sys_info);
}

void dis_line(SystemInfo * Sys_info, Byte * Src, unsigned char line,
	      char ch_buf[32][24])
{
    for (int i = 0; (i < strlen(ch_buf[line])
		     && i < 24); i++) {
	dis_num(Sys_info, Src, ch_buf[line][i], line * 50, i * 50);
    }
    IT8951_Cmd_DisplayArea(line * 50, 0, 50, 1200, 2,
			   (Sys_info->uiImageBufBase), 1);
}

void test_num(SystemInfo * Sys_info, Byte * Src, char ch_buf[32][24])
{
    for (int i = 0; i < 255; i++) {
	sprintf(ch_buf[0], "%d.%d-%d", i, i, i);


	dis_line(Sys_info, Src, 0, ch_buf);
	memset((Src), 0xF0, (gulPanelW * gulPanelH));	//All white
	IT8951_Cmd_LoadImageArea(Src,
				 (Sys_info->uiImageBufBase),
				 0, 0, gulPanelW, gulPanelH);
    }
}
