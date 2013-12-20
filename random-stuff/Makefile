all: spec-elettra

spec-elettra: spec-elettra.c
	gcc -std=gnu99 -g -Wall -Wextra -o spec-elettra spec-elettra.c `pkg-config --cflags --libs gsl glib-2.0`

clean:
	rm spec-elettra

.PHONY: all clean

