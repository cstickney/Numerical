CC=gcc
COPTS=-g -Wall -std=c99
ALL=homography

all: $(ALL)

JUNK= *.o *~ *.dSYM homography

clean:
	-rm -rf $(JUNK)

test: homography
	./homography < boxtop.in

homography: homography.o LUdecomp.o
	$(CC) $(COPTS) $^ -lm -o $@

LUdecomp.o: LUdecomp.c LUdecomp.h
homography.o: homography.c LUdecomp.h

.c.o:
	$(CC) -c $(COPTS) $<