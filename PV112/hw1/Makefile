.PHONY: all clean

CFLAGS=-std=c99 -O2 -lm
LINK_FLAGS=-lglut -lGL -lGLU
CC=gcc

all: hw1

%:%.c
	$(CC) -o $@ $< $(CFLAGS) $(LINK_FLAGS) 

clean:
	rm hw1
