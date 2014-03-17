.PHONY: all clean

PROGRAMS = read generate

all: documentation.pdf $(PROGRAMS)

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

%: %.c
	$(CC) -std=c99 -o $@ $<

clean:
	rm -f *.log *.out *.aux *.toc *.pdf $(PROGRAMS)
