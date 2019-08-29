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

    /*
     * init can socket
     */
    s = create_socket("can0");
    if (s < 0) {
	printf("error: socket create fail");
	return -1;
    }

    int serial_port;
    if ((serial_port = serialOpen("/dev/ttyS0", 9600)) < 0) {	/* open serial port */
	fprintf(stderr, "Unable to open serial device: %s\n",
		strerror(errno));
	return 1;
    }

    if (wiringPiSetup() == -1) {	/* initializes wiringPi setup */
	fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
	return 1;
    }
    Byte src[(1600 * 1200)];
    SystemInfo *Sys_info;	// SystemInfo structure

    path = argv[1];		// arg1: sg path of device
    evpd = page_code = 0;

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

    serialPrintf(serial_port, "Hello world Pi\n\r");

    while (1) {
	struct can_frame *r_frame;

	r_frame = calloc(1, sizeof(*r_frame));

	if (recv_can(s, r_frame) == 0) {
	    dump_can(r_frame);
	    int num = r_frame->data[3] % 10;
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
				r_frame->data[4] << 8 + r_frame->data[5];
			    int valy =
				r_frame->data[6] << 8 + r_frame->data[7];
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
				r_frame->data[3] << 4 + r_frame->data[4];
			    int valy =
				r_frame->data[5] << 4 + r_frame->data[6];
			    sprintf(ch_buf[6], "%4d %4d %2x", valx, valy,
				    r_frame->data[7]);
			    dis_line(Sys_info, src, 6, ch_buf);
			    break;
			}
		    case 0x14:{
			    int vall =
				r_frame->data[3] << 8 + r_frame->data[4];
			    int valr =
				r_frame->data[5] << 8 + r_frame->data[6];
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
