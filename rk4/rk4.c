#include <stdio.h>
#include <math.h>

void RK4(int N, double t, double h, const double X[],
		void (*F)(double t, const double X[], double R[]), double R[]) {
	double K1[N];
	int i;
	F(t, X, K1);

	double T[N], K2[N];
	for (i = 0; i < N; i++)
		T[i] = X[i] + h / 2 * K1[i];
	F(t + h / 2, T, K2);

	double K3[N];
	for (i = 0; i < N; i++)
		T[i] = X[i] + h / 2 * K2[i];
	F(t + h / 2, T, K3);

	double K4[N];
	for (i = 0; i < N; i++)
		T[i] = X[i] + h * K3[i];
	F(t + h, T, K4);

	for (i = 0; i < N; i++)
		R[i] = X[i] + h / 6 * (K1[i] + 2 * (K2[i] + K3[i]) + K4[i]);
}

void Fbaseball(double t, const double X[], double R[]) {
	const double k = 0.002;
	const double g = 32.0;
	R[0] = X[1];
	R[1] = -k * X[1];
	R[2] = X[3];
	R[3] = -k * X[3] - g;
}

void Fmercury(double t, const double X[], double R[]) {
	const double m = 3.301* pow(10,23);
	const double M = 1.9891 * pow(10, 30);
	const double G = 6.67384 * pow(10, -11);

	double r = sqrt(X[0] * X[0] + X[2] * X[2]);
	double F = M*G/r/r;
	double Fx = F*X[0]/r;
	double Fy = F*X[2]/r;

	R[0] = X[1]; //Vx
	R[1] = -Fx; //Ax
	R[2] = X[3]; //Vy
	R[3] = -Fy; //Ay
}

int main() {
	double t = 0;
	double h = 87.969 * 86400 / 100;
	double X[4] = { 46 * pow(10, 9), 0, 0, 58980 };
	for (t = 0.0; t <= h * 100; t += h) {
		printf("%0.10f %0.10f\n", X[0], X[2]);
		RK4(4, t, h, X, Fmercury, X);
	}
//	double t = 0.0;
//	double h = 0.1;
//	double v = 207.0;
//	double theta = 43*M_PI/180;
//	double X[4];
//	X[0] = 0.0; X[1] = v*cos(theta);
//	X[2] = 3.0; X[3] = v*sin(theta);
//	for (t = 0.0; t <= 6.47859; t += 6.47859/100) {
//	  printf("%0.10f %0.10f\n", X[0], X[2]);
//	  RK4(4, t, h, X, Fbaseball, X);
//	}
	return 0;
}
