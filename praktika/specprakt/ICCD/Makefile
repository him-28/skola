.PHONY: all clean

all: ICCD.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.log *.out *.aux ICCD.pdf
