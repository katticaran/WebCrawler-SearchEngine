# Makefile
#Joel Katticaran Fed 2017

#Used Template by David Kotz


VPATH=../lib/bag:../lib/counters:../lib/hashtable:../lib/list:../common:
PROG = crawler
OBJS = crawler.o web.o bag.o counters.o list.o hashtable.o jhash.o
LIBS = -lcurl
#LLIBS = lib/cs50ds.a


CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the crawler
$(PROG): $(OBJS) $(LLIBS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	@echo "Done!"

# crawler source dependencies; add others as needed
crawler.o: web.h bag.h counters.h list.h
hashtable.o: hashtable.h jhash.h
jhash.o: jhash.h
#mycurl.o: mycurl.h
web.o: web.h
bag.o: bag.h 
counters.o: counters.h
list.o: list.h

# build the library
#lib/cs50ds.a: 
#	cd lib; $(MAKE)

clean:
	@rm -f *~
	@rm -f *.o
	@rm -f $(PROG)
	@echo Done Cleaning!
#	@cd lib; $(MAKE) clean
