CC = mpicc
CFLAGS = -O2 -g

all: process_placement.exe

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.exe
