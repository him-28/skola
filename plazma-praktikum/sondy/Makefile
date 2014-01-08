all: sondy.pdf 

%.pdf: %.aux
	pdflatex sondy.tex

%.aux: %.tex
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log sondy.pdf *~
	

