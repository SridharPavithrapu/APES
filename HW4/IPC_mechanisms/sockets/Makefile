CC=gcc

CFLAGS= -O0 -g -Wall -Werror


HFILES= 
CFILES= sockets.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: sockets

clean:
	-rm -f *.o *.d
	-rm -f sockets

sockets: sockets.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
