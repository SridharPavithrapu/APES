CC=gcc

CFLAGS= -O0 -g -pthread -Wall -Werror


HFILES= linked_list.h
CFILES= linked_list.c pthread_assignment.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: final_output

clean:
	-rm -f *.o *.d
	-rm -f final_output

final_output: pthread_assignment.o linked_list.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lm

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
