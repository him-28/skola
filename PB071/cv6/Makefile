PROGRAMS=assert-test fronta
CFLAGS=-std=c99 -Wall -Wextra -pedantic
CC=gcc

all: $(PROGRAMS)

%:%.c
	$(CC) $< $(CFLAGS) -o $@ 
