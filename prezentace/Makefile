SUBDIRS = 14.6.17-Leoben-DFT 14.12.9-Brno-OPVK-report-from-Leoben 14.10.29-Brno-DFT 15.03.25-Brno-DLC-optics 16.07.02-Nantes-SPSSM2016

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
