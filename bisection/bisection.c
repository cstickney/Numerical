/*
 ============================================================================
 Name        : bisection.c
 Author      : Chris Stickney
 Description : bisection program to find where y=0 on a graph
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>

float bisection(float (*f)(float), float a, float b){
	//assume b>a
	assert(b > a);
	float fa = f(a);
	float fb = f(a);

	assert(fa * fb < 0);
	const float mag = (abs(a) +abs(b))/2;
	float c;
	double err = (b-a)/2;
	for(;;){
		c = .5*(a+b);

		if(err <= FLT_EPSILON *(mag))
			return c;
		err /= 2;
		const float fc = f(c);
		if (fa*fc < 0){
			b = c;
			fb = fc;
		} else{
			a = c;
			fa = fc;
		}
	}
}

float f(float x){
	return x * ( x-1 ) -15;
}

int main(void) {
	float r = bisection(f,4,5);
	printf("%f", r);
	char c;
	scanf("%c", &c);

}
