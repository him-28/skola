SUBDIRS = Leoben-17.6.14-DFT Brno-9.12.14-OPVK-report-from-Leoben Brno-29.10.14-DFT

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
