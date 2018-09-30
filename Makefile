SUBDIRS = crawler indexer querier
MAKE = make

.PHONY: subdirs $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@cd $@ && $(MAKE)

clean:
	@cd ./crawler && $(MAKE) clean
	@cd ./indexer && $(MAKE) clean
	@cd ./querier && $(MAKE) clean	
	@rm -f *~
	@rm -f *.o
	@echo Done Cleaning!
