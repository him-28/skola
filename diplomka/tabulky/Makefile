.PHONY: all clean

all: H-table.tex

H-table.tex: ../grafy/vysledky/out-multifit
	../programy/H-table ../grafy/vysledky/out-multifit > H-table.tex

clean:
	rm -f H-table.tex
