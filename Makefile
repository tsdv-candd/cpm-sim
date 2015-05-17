CC=gcc
CFLAGS=-Wall -g

all: cpmsim

clean:
	rm -f *.o cpmsim

cpmsim: cpm.c
	${CC} ${CFLAGS} -o cpmsim cpm.c

