Christopher Stickney
011385713
c.stickney117@gmail.com
-dk.c
-README.txt

My Durand Kerner program constructs a polynomial based on user input and finds all roots of that polynomial. It reads coefficients in from lowest to highest degree, as pairs of doubles, where the first double is the real part of the coefficient and the second double is the imaginary part. After reading in all the pairs, the next highest degree coefficient is set at 1 to give the complete polynomial. After that it comes up with evenly distributed guesses at all the roots, and then iterates on the guesses 50 times or until the changes in x fall below .000001. These iterations are calculated using the durand kerner algorithm described in the assignment description.

Compiled with Cygwin64 using gcc -g -std=c99 -Wall dk.c -o dk -lm
