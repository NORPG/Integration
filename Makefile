

.phony: all clean

all: can.o main.o
	$(CC) -o main $^

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf main *.o

