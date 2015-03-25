.PHONY: all clean

FIGURES = DLCtypes.pdf DLCDOS.pdf T-detail-multifit2.pdf deconv-multifit2.pdf CH30deconv.pdf thickness.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -f *~ $(FIGURES)
