/*
 ============================================================================
Name        : relerror.c
Author      : Chris Stickney
Description : program that prints n and the corresponding upper bound for the relative error using Equation 12 for n = 1 to 15.
From this table determine the smallest n such that the relative error is guaranteed to be below EPSILON = 1.19209x10-7
 ============================================================================
 */

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int factorial(int n);


int main(void) {
	
	int subEpsilon;
	int n = 1;
	int checkif = 0;

	while(n < 16){
		double upperBoundError = sqrt(2)/ factorial(n+1)* (pow(_M_LN2/2, n+1));
		double relativeError = sqrt(2) * upperBoundError;
		double epsilon = 0.000000119209; // 1.19209*10^-7
		if(relativeError<= epsilon && checkif == 0){
			subEpsilon = n;

			checkif = 1;

		}
		
	printf("at %i the upper bound error is %f \n" , n, upperBoundError);
		++n;
	}
	printf("the smallest n where relative error is guaranteed to be below 1.19209*10^-7 is %i\n", subEpsilon);
	getchar();
	return 0;
}


int factorial(int a){
	int factorial =0;
	if(a>=0){
		factorial=1;
	}
	else{
		factorial=-1;
	}
	while(a>1){
		factorial = factorial*a;
		--a;
	}
	return factorial;
}
