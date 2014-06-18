.PHONY: all clean

all: erasmus_motivace.pdf

%.pdf: %.tex
	pdflatex $<

clean:
	rm -f erasmus_motivace.pdf *.out *.log *.aux *~
