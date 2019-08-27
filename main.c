#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "can.h"
#include "IT8951_USB.h"

unsigned char sense_buffer[SENSE_LEN];
unsigned char data_buffer[BLOCK_LEN * 256];

DWord gulPanelW, gulPanelH;

char *path;
int evpd, page_code;

int main(int argc, char *argv[])
{
    int s;

    /*
     * init can socket
     */
    s = create_socket("can0");
    if (s < 0) {
	printf("error: socket create fail");
	return -1;
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

    while (1) {
	struct can_frame *r_frame;

	r_frame = calloc(1, sizeof(*r_frame));

	if (recv_can(s, r_frame) == 0) {
	    dump_can(r_frame);
	    int num = r_frame->data[3] % 10;
	    if (r_frame->data[0] == 0x03) {
		if (r_frame->data[1] == 0x02) {
		    memset((src), 0xF0, (50 * 100));
		    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 800, 600, 50, 100);	//_

		    switch (r_frame->data[2]) {
		    case 0x10:
			dis_num(Sys_info, src, num, 800, 600);
			IT8951_Cmd_DisplayArea(800, 600, 50, 50, 2,
					       (Sys_info->uiImageBufBase),
					       1);
			break;
		    case 0x11:
			break;
		    case 0x12:
			break;
		    case 0x13:
			break;
		    case 0x14:
			break;
		    case 0x15:
			break;
		    }
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
