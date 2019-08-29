CFLAGS = -g -Wall
.phony: all clean
LIBS = -lwiringPi

all: can.o main.o IT8951_CMD.o IT8951_USB.o
	$(CC) $(CFLAGS) $(LIBS) -o main $^

%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

clean:
	rm -rf main *.o

