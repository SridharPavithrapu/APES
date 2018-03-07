CC=gcc

CFLAGS= -O0 -g -Wall -Werror


HFILES= 
CFILES= pipes.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: pipes

clean:
	-rm -f *.o *.d
	-rm -f pipes

pipes: pipes.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
