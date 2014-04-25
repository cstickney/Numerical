/*
 ============================================================================
 Name        : dk.c
 Author      : Chris Stickney
 Description : Durand-Kerner project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define M_PI 3.141592653589793238467
void printPoly(int degree, double complex c[21], double error);


int main(void) {
	double complex c[21];
	double error = .000001;
	int kMax = 50;
	int degree;//degree = n
	double real,imag;
	int i=0;

	while(scanf("%lf%lf", &real,&imag) == 2){//reads through .in from LOWEST to HIGHEST
		c[i++]= real+imag*I;
	}
	c[i] = 1; //highest degree term  c =1
	degree=i;//degree of polynomial

	printPoly(degree, c, error);//displays the complex polynomial


	//guess//////////////////////////////////////////////////////////////////
	double maxC = cabs(c[degree]);
	int degCtr = degree -1;

	while(degCtr >=0){
		if(maxC < cabs(c[degCtr])){
			maxC = cabs(c[degCtr]);
		}
		--degCtr;
	}

	double R = maxC+1;
	int a = 0;
	double complex x[20];
	double theta[20];

	while(a <= degree -1){
		theta[a] = 2* M_PI * a /degree;
		x[a] = (cos(theta[a]) + sin(theta[a]) * I) * R;
		++a;
	}
	a=0;
	printf("\n\niter 1");
	while(a <= degree -1){
		printf("\nx[%i] = %.10f + %.10f i",a, creal(x[a]), cimag(x[a]));
		++a;
	}

	//iterate on guess//////////////////////////////////////////////////////////
	int k = 2;
	double complex deltaX[20];

	while(k<= kMax){
		double deltaXMax = 0;
		int j = 0;
		while(j <= degree-1){
			//figure 3: Q
			int i=0;
			double complex Q = 1;
			while(i<=degree-1){
				if(i==j){
					++i;
				}
				else{
					Q = Q*(x[j] - x[i]);
					++i;
				}
			}


			//figure 1: f(xj)
			i=degree-1;
			double complex f=0;
			if(degree !=0){
				f = 1;
				while(i >= 0){
					f = c[i] + f*x[j];
					--i;
				}
			}
			deltaX[j] = -1*f/Q;


			if(cabs(deltaX[j]) > deltaXMax){
				deltaXMax = cabs(deltaX[j]);
			}
			++j;
		}

		if(cabs(deltaXMax) / error <1){
			k=kMax;
		}
		else{
			printf("\niter %i", k);
			//printf("\ndeltaXMax = %.7f", deltaXMax);
			j=0;
			while(j <= degree -1){
				x[j] = x[j] + deltaX[j];
				printf("\nx[%i] = %.10f + %.10f i",j, creal(x[j]), cimag(x[j]));
				++j;
			}
		}
		++k;
	}
}


void printPoly(int degree, double complex c[21], double error){//displays the complex polynomial
	printf("\nf(x) = x^%i ", degree);
	--degree;
	while(degree >= 1){
		if(c[degree] == 0){}//does not print the term if coefficient is zero
		else if(creal(c[degree]) == 0) {//displays 1x^degree as
			if(cimag(c[degree]) - 1 < error){// removes c if x
				printf("+ ix^%i ", degree );
			}
			else if(cimag(c[degree]) + 1 < error){
				printf("+ -ix^%i ", degree );
			}
			else{
				printf("+ %gix^%i ", cimag(c[degree]), degree );
			}
		}
		else if(cimag(c[degree]) == 0){
			if(creal(c[degree] - 1) < error){
				printf("+ x^%i ", degree );
			}
			else if(creal(c[degree] + 1) < error){
				printf("+ -x^%i ", degree );
			}
			else{
				printf("+ %gx^%i ",creal(c[degree]), degree );
			}
		}
		else{
			if(fabs(cimag(c[degree]) - 1) < error){
				printf("+ (%g + i)x^%i ",creal(c[degree]), degree );
			}
			else{
				printf("+ (%g + %gi)x^%i ",creal(c[degree]), cimag(c[degree]), degree );
			}
		}
		degree--;
	}
	if(creal(c[0]) != 0){
		printf("+ %g ", creal(c[0]));
	}
	if(cimag(c[0]) != 0){
		if(fabs(cimag(c[degree]) - 1) < error){
			printf("+ i");
		}
		else{
			printf("+ %gi", cimag(c[0]));
		}
	}
}