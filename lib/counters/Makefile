CC=gcc
CFLAGS=-std=c11 -Wall -pedantic -ggdb
DEPS=counters.h
OBJ=counterstest.o counters.o
OUTPUT=counterstest

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTPUT): $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	@rm -f *~
	@rm -f *.o
	@rm -f $(OUTPUT)
	@rm -f names
