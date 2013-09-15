all: vyhasinani.pdf 

%.pdf: %.tex %.aux
	pdflatex $<

%.aux: %.tex
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log vyhasinani.pdf *~
	

