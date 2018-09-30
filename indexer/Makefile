VPATH=../lib/bag:../lib/counters:../lib/hashtableIndex:../lib/list:../common:
PROG = indexer
PROG2 = indextest
OBJS = indexer.o web.o bag.o counters.o list.o hashtable.o jhash.o file.o word.o
OBJS2 = indextest.o file.o counters.o hashtable.o jhash.o
LIBS = -lcurl

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

all: $(PROG) $(PROG2)

$(PROG2): $(OBJS2) $(LLIBS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(PROG): $(OBJS) $(LLIBS)
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	@echo "Done!"

crawler.o: web.h bag.h counters.h list.h
hashtable.o: hashtable.h jhash.h counters.h
jhash.o: jhash.h
#mycurl.o: mycurl.h
web.o: web.h
word.o: word.h
file.o: file.h
bag.o: bag.h 
counters.o: counters.h
list.o: list.h

clean:
	@rm -f *~
	@rm -f *.o
	@rm -f $(PROG) $(PROG2)
	@echo Done Cleaning!
