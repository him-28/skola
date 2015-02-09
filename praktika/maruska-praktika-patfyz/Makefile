.PHONY: all clean

FILES = DM/DM.pdf ikterus/ikterus.pdf kuze/kuze.pdf tromboza/tromboza.pdf

all: $(FILES)

%.pdf: %.tex
	cd $(<D); \
	pdflatex $(<F); \
	cd ..

clean:
	rm -f $(FILES)
	for file in $(FILES); do \
		cd $$(dirname $$file); \
		rm -f *.out *.aux *.log *~; \
		cd ..; \
	done
