/*
 ============================================================================
 Name        : homography.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LUdecomp.h"

int main(void) {
	int N;
	double x[4];
	double y[4];
	double x2[4];
	double y2[4];

	scanf("%d", &N);
	int i = 0;
	while(i < N){//N source points
		scanf("%lf %lf", &x[i], &y[i]);
		i++;
	}
	i=0;
	while (i < N){
		scanf("%lf %lf", &x2[i], &y2[i]);
		i++;
	}
	double B[8];
	i=0;
	int j=0;
	while(i<N){
		B[j++] = x2[i];
		B[j++] = y2[i];
		i++;
	}
	double A[8][8] = {
		{x[0], y[0], 1, 0, 0, 0, -x[0]*x2[0], -y[0]*x2[0]},
		{0, 0, 0, x[0], y[0], 1, -x[0]*y2[0], -y[0]*y2[0]},
		{x[1], y[1], 1, 0, 0, 0, -x[1]*x2[1], -y[1]*x2[1]},
		{0, 0, 0, x[1], y[1], 1, -x[1]*y2[1], -y[1]*y2[1]},
		{x[2], y[2], 1, 0, 0, 0, -x[2]*x2[2], -y[2]*x2[2]},
		{0, 0, 0, x[2], y[2], 1, -x[2]*y2[2], -y[2]*y2[2]},
		{x[3], y[3], 1, 0, 0, 0, -x[3]*x2[3], -y[3]*x2[3]},
		{0, 0, 0, x[3], y[3], 1, -x[3]*y2[3], -y[3]*y2[3]}
	};
	  const double *A_[8] = {
			  A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7],
	  };
	  const double b[] = {B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7]};


	LUdecomp *LU = LUdecompose(2*N, A_);
	double h[2*N];
	LUsolve(LU, b, h);
	printf("%.10f %.10f %.10f \n%.10f %.10f %.10f \n%.10f %.10f 1",h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7]);
	LUdestroy(LU);
}
