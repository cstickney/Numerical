/*
 ============================================================================
 
Name        : exp.c
 
Author      : Chris Stickney
 
Description : computes the taylor series for e^x (c=0) and compares to e^x
 ============================================================================
 */


#include <stdio.h>

#include <stdlib.h>

#include <math.h>




float myexp(float x);

int factorial(int n);



int main(void) {
	
float x=0.0;

//	printf("enter x \n");

//	scanf("%f", &x);
	
float n=-11;
	
while(n <=20){
		
	float relerror = abs(myexp(n) - exp(n)) / abs(exp(x));


		printf("x = %f,\nmyexp(x) = %f,\nexp(x) = %f,\nrelerror = %f\n\n", n, myexp(n), exp(n), relerror);

		printf("press return to continue \n");

		char c;

		scanf("%c", &c);

		n=n+1;

	}


	scanf("%f", &x);

	return 0;

}

float myexp(float x){

	float twom;

	float eu;

	float z= x*1.4426950408889634074;//M_LOG2E wouldnt compile.

	int m = round(z);

	float w = z-m;

	float u = w*_M_LN2;

	//n=7;

	//e^x = 2^m*e^u

	//compute 2^m

	if(m>=0){

		twom = (1<<m);

	}

	else{
		m=-m;

		twom = 1<<m;

		twom= 1/twom;

	}

	//compute e^u

	eu = 1 + u*(1+u/2*(1+u/3*(1+u/4*(1+u/5*(1+u/6)))));


	float ex = eu*twom;

//	printf("x = %f\n", x);

//	printf("z = %f\n", z);

//	printf("m = %i\n", m);

//	printf("w = %f\n", w);

//	printf("u = %f\n", u);

//	printf("2^m = %f\n", twom);

//	printf("e^u = %f\n", eu);

//	printf("~e^x = %f\n", ex);

	return ex;

}



int factorial(int n){

	int factorial;

	if(n>=0){

		n=1;

	}

	else{
		n=-1;

	}

	while(n>1){

		factorial = factorial*n;

		--n;

	}


	return factorial;

}
