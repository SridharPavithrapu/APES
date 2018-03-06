CC=gcc

CFLAGS= -O0 -g -Wall -Werror


HFILES= 
CFILES= message_queue.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: message_queue

clean:
	-rm -f *.o *.d
	-rm -f message_queue

message_queue: message_queue.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
