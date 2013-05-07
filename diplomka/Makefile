all: pdffinal

pdffinal: pdfdraft2
	pdflatex diplomka.tex

pdfdraft2: bibtex
	pdflatex diplomka.tex

grafika: grafika/DLCDOS.pdf grafika/layerscheme.pdf grafika/reaktor.pdf grafika/dlcgrowth.pdf grafika/dlcgrowthH.pdf

grafika/DLCDOS.pdf:
	inkscape --without-gui --export-pdf=grafika/DLCDOS.pdf grafika/DLCDOS.svg
grafika/layerscheme.pdf:
	inkscape --without-gui --export-pdf=grafika/layerscheme.pdf grafika/layerscheme.svg
grafika/reaktor.pdf:
	inkscape --without-gui --export-pdf=grafika/reaktor.pdf grafika/reaktor.svg
grafika/dlcgrowth.pdf:
	inkscape --without-gui --export-pdf=grafika/dlcgrowth.pdf grafika/dlcgrowth.svg
grafika/dlcgrowthH.pdf:
	inkscape --without-gui --export-pdf=grafika/dlcgrowthH.pdf grafika/dlcgrowthH.svg

programy/deconvolute:
	gcc programy/deconvolute.c -o programy/deconvolute -std=c99 -g

programy/H-table:
	gcc programy/H-table.c -o programy/H-table -std=c99 -g

grafy: programy/deconvolute grafy/R-multifit.pdf grafy/T-multifit.pdf grafy/T-detail-multifit.pdf grafy/deconv-multifit.pdf grafy/ell-multifit.pdf grafy/deconv-multifit2.pdf grafy/R-multifit2.pdf grafy/Si-detail.pdf grafy/transition.pdf grafy/Hdif.pdf grafy/T-detail-multifit2.pdf grafy/N.pdf grafy/ell-multifit2.pdf grafy/T-multifit2.pdf

grafy/CH30Adeconv.gpi:
	programy/deconvolute vysledky/out-multifit 1 > grafy/CH30Adeconv.gpi
grafy/CH30Cdeconv.gpi:
	programy/deconvolute vysledky/out-CH30C 0 > grafy/CH30Cdeconv.gpi
grafy/CH30Ddeconv.gpi:
	programy/deconvolute vysledky/out-CH30D 0 > grafy/CH30Ddeconv.gpi
grafy/CH87Adeconv.gpi:
	programy/deconvolute vysledky/out-CH87A 0 > grafy/CH87Adeconv.gpi
grafy/CH89Adeconv.gpi:
	programy/deconvolute vysledky/out-CH89A 0 > grafy/CH89Adeconv.gpi
grafy/CH88Adeconv.gpi:
	programy/deconvolute vysledky/out-multifit 2 > grafy/CH88Adeconv.gpi
grafy/CH90Adeconv.gpi:
	programy/deconvolute vysledky/out-multifit 3 > grafy/CH90Adeconv.gpi
grafy/CH83Adeconv.gpi:
	programy/deconvolute vysledky/out-multifit 4 > grafy/CH83Adeconv.gpi
grafy/R-multifit.pdf:
	gnuplot grafy/R-multifit.gpi > grafy/R-multifit.pdf
grafy/R-multifit2.pdf:
	gnuplot grafy/R-multifit2.gpi > grafy/R-multifit2.pdf
grafy/T-multifit.pdf:
	gnuplot grafy/T-multifit.gpi > grafy/T-multifit.pdf
grafy/T-multifit2.pdf:
	gnuplot grafy/T-multifit2.gpi > grafy/T-multifit2.pdf
grafy/T-detail-multifit.pdf:
	gnuplot grafy/T-detail-multifit.gpi > grafy/T-detail-multifit.pdf
grafy/T-detail-multifit2.pdf:
	gnuplot grafy/T-detail-multifit2.gpi > grafy/T-detail-multifit2.pdf
grafy/deconv-multifit.pdf: grafy/CH30Adeconv.gpi grafy/CH88Adeconv.gpi grafy/CH90Adeconv.gpi grafy/CH83Adeconv.gpi
	gnuplot grafy/deconv-multifit.gpi > grafy/deconv-multifit.pdf
grafy/deconv-multifit2.pdf: grafy/CH30Cdeconv.gpi grafy/CH30Ddeconv.gpi grafy/CH87Adeconv.gpi grafy/CH89Adeconv.gpi
	gnuplot grafy/deconv-multifit2.gpi > grafy/deconv-multifit2.pdf
grafy/ell-multifit.pdf:
	gnuplot grafy/ell-multifit.gpi > grafy/ell-multifit.pdf
grafy/ell-multifit2.pdf:
	gnuplot grafy/ell-multifit2.gpi > grafy/ell-multifit2.pdf
grafy/Si-detail.pdf:
	gnuplot grafy/Si-detail.gpi > grafy/Si-detail.pdf
grafy/transition.pdf:
	gnuplot grafy/transition.gpi > grafy/transition.pdf
grafy/Hdif.pdf:
	gnuplot grafy/Hdif.gpi > grafy/Hdif.pdf
grafy/N.pdf:
	gnuplot grafy/N.gpi > grafy/N.pdf

tabulky: tabulky/H-table.tex

tabulky/H-table.tex: programy/H-table
	programy/H-table vysledky/out-multifit > tabulky/H-table.tex

bibtex: pdfdraft
	bibtex diplomka

pdfdraft: grafika grafy tabulky
	pdflatex diplomka.tex

clean:
	rm grafika/DLCDOS.pdf grafika/layerscheme.pdf grafika/reaktor.pdf grafika/dlcgrowth.pdf grafika/dlcgrowthH.pdf diplomka.aux diplomka.bbl diplomka.log diplomka.out diplomka.idx diplomka.blg diplomka.toc diplomka.pdf programy/deconvolute grafy/CH30Adeconv.gpi grafy/CH30Cdeconv.gpi grafy/CH30Ddeconv.gpi grafy/CH83Adeconv.gpi grafy/CH87Adeconv.gpi grafy/CH88Adeconv.gpi grafy/CH89Adeconv.gpi grafy/CH90Adeconv.gpi grafy/T-multifit.pdf grafy/R-multifit.pdf grafy/T-detail-multifit.pdf tabulky/H-table.tex grafy/ell-multifit.pdf programy/H-table grafy/R-multifit2.pdf grafy/Si-detail.pdf grafy/transition.pdf grafy/Hdif.pdf grafy/T-detail-multifit2.pdf grafy/N.pdf grafy/ell-multifit2.pdf grafy/T-multifit2.pdf grafy/deconv-multifit.pdf grafy/deconv-multifit2.pdf
