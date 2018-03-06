CC=gcc

CFLAGS= -O0 -g -Wall -Werror


HFILES= 
CFILES= shared_memory.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: shared_memory

clean:
	-rm -f *.o *.d
	-rm -f shared_memory

shared_memory: shared_memory.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
