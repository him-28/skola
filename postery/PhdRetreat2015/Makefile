FIGURES := $(shell sed -r 's/^[^%%]*\\includegraphics(\[[^]]+\])?\{([^}]+)\}.*/\2/;t;d' poster.tex)

.PHONY: all clean figures

all: poster.pdf

poster.pdf: poster.tex figures.stamp $(FIGURES)
	pdflatex $<

figures.stamp: figures
	@for x in $(FIGURES); do \
		if test $$x -nt figures.stamp; then \
			touch -r $$x figures.stamp; \
		fi; \
	done

figures:
	$(MAKE) -C $@

%.pdf: %.svg
	inkscape --without-gui --export-area-drawing --export-text-to-path --export-pdf=$@ $<

clean:
	rm -f *.aux *.log poster.pdf figures.stamp *~
	$(MAKE) -C figures $@

