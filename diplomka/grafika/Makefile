FILES = DLCDOS.pdf layerscheme.pdf reaktor.pdf dlcgrowth.pdf dlcgrowthH.pdf schema-elipsometru.pdf rutherford.pdf ERDA.pdf DLCtypes.pdf
.PHONY: all clean

all: $(FILES)

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -f $(FILES)
