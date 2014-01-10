FILES = R-multifit.pdf T-multifit.pdf T-detail-multifit.pdf deconv-multifit.pdf ell-multifit.pdf deconv-multifit2.pdf R-multifit2.pdf Si-detail.pdf transition.pdf Hdif.pdf T-detail-multifit2.pdf N.pdf ell-multifit2.pdf T-multifit2.pdf

.PHONY: all clean

all: $(FILES)

%.pdf: %.gpi
	gnuplot $< > $@

deconv-multifit.pdf: CH30Adeconv.gpi CH88Adeconv.gpi CH90Adeconv.gpi CH83Adeconv.gpi
deconv-multifit2.pdf: CH30Cdeconv.gpi CH30Ddeconv.gpi CH87Adeconv.gpi CH89Adeconv.gpi

CH30Adeconv.gpi:
	../programy/deconvolute vysledky/out-multifit 1 0.09 > $@
CH30Cdeconv.gpi:
	../programy/deconvolute vysledky/out-CH30C 0 0.097 > $@
CH30Ddeconv.gpi:
	../programy/deconvolute vysledky/out-CH30D 0 0.105 > $@
CH87Adeconv.gpi:
	../programy/deconvolute vysledky/out-CH87A 0 0.093 > $@
CH89Adeconv.gpi:
	../programy/deconvolute vysledky/out-CH89A 0 0.078 > $@
CH88Adeconv.gpi:
	../programy/deconvolute vysledky/out-multifit 2 0.083 > $@
CH90Adeconv.gpi:
	../programy/deconvolute vysledky/out-multifit 3 0.073 > $@
CH83Adeconv.gpi:
	../programy/deconvolute vysledky/out-multifit 4 0.092 > $@

clean:
	rm -f $(FILES) *deconv.gpi
