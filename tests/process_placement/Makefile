CC = mpicc
CFLAGS = -O2 -g -Wall

all: process_placement.exe

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.exe

install: all
	cp process_placement.exe /usr/bin
