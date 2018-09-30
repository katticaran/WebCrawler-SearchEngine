CC=gcc
CFLAGS=-std=c11 -Wall -pedantic -ggdb
DEPS=bag.h
OBJ=bagtest.o bag.o
OUTPUT=bagtest

#%.o: %.c $(DEPS)
#	$(CC) $(CFLAGS) -c -o $@ $<
$(OUTPUT): $(OBJ)
	gcc $(CFLAGS) -o $(OUTPUT) $(OBJ)

bagtest.o: bag.h
bag.o: bag.h


clean:
	@rm -f *~
	@rm -f *.o
	@rm -f $(OUTPUT)	
	@rm -f names
