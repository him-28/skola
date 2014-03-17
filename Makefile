SUBDIRS = diplomka bakalarka specprakt plazma-praktikum F1400

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
