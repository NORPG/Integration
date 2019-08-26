#include <stdio.h>
#include <stdlib.h>
#include "can.h"

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

    while (1) {
	struct can_frame *r_frame;

	r_frame = calloc(1, sizeof(*r_frame));

	if (recv_can(s, r_frame) == 0) {
	    dump_can(r_frame);
	}

	free(r_frame);
	sleep(1);
    }
}
