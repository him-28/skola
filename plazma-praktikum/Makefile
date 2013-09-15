SUBDIRS = ecr koncentrace paschen peroxid rozdelfunkce sondy townsend vyhasinani

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
