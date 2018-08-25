SUBDIRS := $(wildcard */.)

all: $(SUBDIRS)
$(SUBDIRS):
	@make --no-print-directory -C $@

clean:
	find . -name output | xargs rm
	find . -name *.orig | xargs rm

.PHONY: all $(SUBDIRS) clean
