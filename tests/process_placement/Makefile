CC = mpicc
CFLAGS = -O2 -g -Wall

all: process_placement.exe

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.exe

install: process_placement.exe run_process_placement.sh
	cp process_placement.exe /usr/bin
	cp run_process_placement.sh /usr/bin
