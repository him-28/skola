CFLAGS = -std=gnu99 -g -Wall -Wextra

all: spec-elettra parse

spec-elettra: spec-elettra.c
	gcc $(CFLAGS) -o spec-elettra spec-elettra.c `pkg-config --cflags --libs gsl glib-2.0`

parse: parse.c
	gcc $(CFLAGS) -o parse parse.c 

clean:
	rm spec-elettra parse

.PHONY: all clean

