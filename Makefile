

.phony: all clean

all: can.o main.o IT8951_CMD.o IT8951_USB.o
	$(CC) -o main $^

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf main *.o

