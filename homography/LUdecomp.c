/*
 ============================================================================
 Name        : LUdecomp.c
 Author      : Chris Stickney
 Description : Solves linear equations with LU decomposition.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LUdecomp.h"
#include <math.h>

LUdecomp *LUdecompose(int N, const double **A){
	LUdecomp *z = malloc(sizeof (LUdecomp));
	z->N = N;
	z->d = +1;
	z->LU = malloc(N*sizeof(double *));
	for (int r=0; r < N; r++)
		z->LU[r] = malloc(N*sizeof(double));
	z->mutate = malloc(N*sizeof(short));
	int i, j, k;

	for(i=0; i<N; i++){
		z->mutate[i] = i;
		for(j=0; j<N; j++){
			z->LU[i][j] = A[i][j];
		}
	}
	for(j=0; j<N; j++){
		for(i=0; i<=j; i++){
			double sum = 0;
			for(k=0; k<i; k++)
				sum = sum + z->LU[i][k] * z->LU[k][j];
			z->LU[i][j] = z->LU[i][j] - sum;
		}
		double p = fabs(z->LU[j][j]);
		int n=j;
		for(i=j+1; i<N; i++){
			double sum = 0;
			for(k=0; k<j; k++)
				sum = sum + z->LU[i][k] * z->LU[k][j];
			z->LU[i][j] = z->LU[i][j] - sum;
			if(fabs(z->LU[i][j])>p){
				p=fabs(z->LU[i][j]);
				n=i;
			}
		}
		if(p==0){
			LUdestroy(z);
			printf("SINGULAR MATRIX! Aborting...\n");
			return NULL;
		}
		if(n!=j){
			double* tempRow= z->LU[n];
			z->LU[n] = z->LU[j];
			z->LU[j] = tempRow;
			short tempMutate = z->mutate[n];
			z->mutate[n] = z->mutate[j];
			z->mutate[j] = tempMutate;
			z->d=-z->d;
		}
		for(i=j+1; i<N; i++){
			z->LU[i][j] = z->LU[i][j]/z->LU[j][j];
		}
	}
	return z;
}

void LUdestroy(LUdecomp *LU){//deallocates the data allocated in LUdecompose().
	int r;
	for (r=0; r < LU->N ; r++)
			free(LU->LU[r]);
	free(LU->LU);
	free(LU->mutate);
	free(LU);
}

void LUsolve(LUdecomp *decomp, const double *b, double *x){//solves the system Ax = b for x:
	double y[decomp->N];
	y[0] = b[decomp->mutate[0]];
	int i, j;
	for(i=1; i<decomp->N; i++){
		double sum = 0;
		for(j=0; j<i; j++){
			sum = sum + decomp->LU[i][j] * y[j];
		}
		y[i] = b[decomp->mutate[i]] - sum;
	}
	x[decomp->N - 1] = y[decomp->N - 1]/decomp->LU[decomp->N -1][decomp->N -1];
	for(i=decomp->N-2; i>=0; i--){
		double sum = 0;
		for(j = i+1; j<decomp->N; j++){
			sum = sum +  decomp->LU[i][j] * x[j];
		}
		x[i] = 1/decomp->LU[i][i] * (y[i] - sum);
	}
}
