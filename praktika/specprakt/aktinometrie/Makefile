.PHONY: all clean

all: aktinometrie.pdf

aktinometrie.pdf: aktinometrie.tex speed_constants
	pdflatex $<
	pdflatex $<

%: %.c
	$(CC) -std=gnu90 -lm -o $@ $<

clean:
	rm -f *.log *.out *.aux aktinometrie.pdf speed_constants
