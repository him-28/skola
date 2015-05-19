.PHONY: all clean

FIGURES = gap.pdf SiTiO2-eps.pdf SiTiO2-dos.pdf n-anatase.pdf near-gap-eps.pdf compare.pdf

all: $(FIGURES)

data:
	cp /home/franta/Documents/DATA/SiTiO/N15BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N15BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N17BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N17BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N19BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N19BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N21BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N21BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N23BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N23BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N25BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N25BS.nk
	cp /home/franta/Documents/DATA/SiTiO/N27BS/out-final .
	extractAD-oc.py out-final
	cp f1.nk SiTiO-N27BS.nk

epsi%.pdf: epsi%.gpi *.nk
	gnuplot $< > $@

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f $(FIGURES) *~
