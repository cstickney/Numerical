Christopher Stickney
011385713
c.stickney117@gmail.com

-homography.c
-LUdecomp.c
-LUdecomp.h
-boxtop.in
-Makefile
-README.txt

This program uses LU decomposition to solve a set of linear equations for x. 
This program only deals with systems where N=4, and does not account for overdetermined systems.
Compiles and runs with: make test
to change what .in file this uses, either change line 13 of the makefile to use your file or type
"./homography < YOURFILE.in" once it has been compiled.
