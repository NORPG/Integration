CFLAG = -g
.phony: all clean

all: can.o main.o IT8951_CMD.o IT8951_USB.o
	$(CC) $(CFLAG) -o main $^

%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $<

clean:
	rm -rf main *.o

