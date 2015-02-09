all: vyhasinani.pdf 

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log vyhasinani.pdf *~
	

