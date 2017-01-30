CC = mpicc
CFLAGS = -O2 -g

all: hello.exe

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.exe
