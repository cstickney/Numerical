CC=gcc
COPTS=-g -Wall -std=c99
ALL=LUtest

all: $(ALL)

JUNK= *.o *~ *.dSYM LUtest

clean:
	-rm -rf $(JUNK)

test: LUtest
	./LUtest

LUtest: LUtest.o LUdecomp.o
	$(CC) $(COPTS) $^ -lm -o $@

LUdecomp.o: LUdecomp.c LUdecomp.h
LUtest.o: LUtest.c LUdecomp.h

.c.o:
	$(CC) -c $(COPTS) $<