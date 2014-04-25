/*
 ============================================================================
 Name        : pi.c
 Author      : Chris Stickney
 Description : Estimates the value of pi using composite trapezoid rule, simpsons 1/3 rule, simpsons 3/8 rule, boole's rule
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

long double trap(long double (*f)(long double),//function
		long double a, long double b, //interval
		int n);
long double simpsons(long double (*f)(long double),//function
		long double a, long double b, //interval
		int n);
long double simpsons38(long double (*f)(long double),//function
		long double a, long double b, //interval
		int n);
long double booles(long double (*f)(long double),//function
		long double a, long double b, //interval
		int n);
long double f(long double x);
long double fabslDontWork(long double value);



int main(void) {
  const unsigned maxn = 800000;
  for (unsigned n = 12; n <= maxn; n *= 2) {
    long double I_trap = trap(f, 0, 1, n);
    long double error_trap = fabslDontWork(M_PI - I_trap);
    const long double I_simp = simpsons(f, 0, 1, n);
    const long double error_simp = fabslDontWork(M_PI - I_simp);
    const long double I_simp38 = simpsons38(f, 0, 1, n);
    const long double error_simp38 = fabslDontWork(M_PI - I_simp38);
    const long double I_booles = booles(f, 0, 1, n);
    const long double error_booles = fabslDontWork(M_PI - I_booles);
    printf("%5d %0.10Le %0.10Le %0.10Le %0.10Le\n", n,
	   error_trap, error_simp, error_simp38, error_booles);

  }
  return 0;
}
long double trap(long double (*f)(long double), long double a, long double b, int n){
	long double h=(b-a)/n;
	int i=0;
	long double answer = 0;

	while(i<n){
		answer = answer + f(a+i*h) + f(a+(i+1)*h);
		++i;
	}
	answer =(h/2)*answer;
	return answer;
}
long double simpsons(long double (*f)(long double), long double a, long double b, int n){
	long double h=(b-a)/n;
	long double answer = f(a) + f(b);
	int i=1;
	while(i<=n/2-1){
		answer = answer +2*f(a+2*i*h);
		++i;
	}
	i=1;
	while(i<=n/2){
		answer = answer +4*f(a+(2*i-1)*h);
		++i;
	}
	answer =(h/3)*answer;
	return answer;
}
long double simpsons38(long double (*f)(long double), long double a, long double b, int n){
	long double h=(b-a)/n;
	int m=n/3;
	int i=1;
	long double answer = 0;
	while(i<=m){
		answer = answer + f(a+3*i*h) + 3*(f(a+(3*i-1)*h) + f(a+(3*i-2)*h)) + f(a+(3*i-3)*h);
		++i;
	}
	answer =(3*h/8)*answer;
	return answer;

}
long double booles(long double (*f)(long double), long double a, long double b, int n){
	long double h=(b-a)/n;
	int m=n/4;
	int i=1;
	long double answer = 0;
	while(i<=m){
		answer = answer + 7*f(a+4*i*h) +32*f(a+(4*i-1)*h)+ 12*f(a+(4*i-2)*h) + 32*f(a+(4*i-3)*h) + 7*f(a+(4*i-4)*h);
		++i;
	}
	answer =(2*h/45)*answer;
	return answer;


	return (7*f(a) +32*f(a+h) +12*f(a+2*h) +32*f(a+3*h) +  7*f(a+4*h));
}

long double f(long double x) {
//	printf("f(x) = %0.10Le\n",4/(1+x*x));
  return 4/(1+x*x);
}

long double fabslDontWork(long double value){
	if(value <0){
		value = -value;
	}
	return value;
}

