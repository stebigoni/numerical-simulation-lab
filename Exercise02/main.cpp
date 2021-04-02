#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "blocking.h"
#include "print.h"


using namespace std;

double integrand(double x)
{
	return M_PI/2 * cos(M_PI/2*x);
}

double distrib(double x)
{
	return M_PI/2*(1-M_PI*M_PI*x*x/8);
}

void dist(double *X, double *Y, double *Z, double*r2, int N, int M);

int main (int argc, char *argv[])
{

	/************* INITIALIZING RANDOM GENERATOR ***********/

	Random rnd;

	rnd.LoadSeed("Primes","seed.in");//Setting up the generator


	/************************* EXERCISE 02.1 *************************/

	int M = pow(10,5); //number of steps
	int N = 100;	//number of blocks
	Blocking blk(M,N);

	//uniform sampling
	double r[M];	//random array

	for (int i=0; i<M; i++) r[i] = rnd.Rannyu();//Generating M numbers in [0,1]

	double g[M];
	for(int i=0;i<M;i++) g[i] = integrand(r[i]);	//evaluating function
	blk.CAvgs(g);
	blk.CStDev();
	blk.Output("uniform.dat");

	//importance sampling con retta p(x) = 2-2x
	double x[M];
	for(int i=0;i<M;i++)
	{
		x[i] = 1-pow(1-rnd.Rannyu(),0.5);
		g[i] = integrand(x[i])/(2-2*x[i]);
	}

	blk.CAvgs(g);
	blk.CStDev();
	blk.Output("importance.dat");



	/************************* EXERCISE 02.2 *************************/
	//RANDOM WALK ON 3D LATTICE

	M = pow(10,4); // number of walks
	N = 100; //number of steps in a walk

	//Space coordinates
	double *X = new double[M*N];
	double *Y = new double[M*N];
	double *Z = new double[M*N];
	double *r2 = new double[M*N]; //square distance from the origin

	//PERFORM WALK
	for(int i=0;i<M-1;i++){
		X[N*i] = 0;
		Y[N*i] = 0;
		Z[N*i] = 0;
		for(int j=0;j<N;j++){
			int k = N*i+j;
			X[k+1] = X[k] + rnd.Walk();
			Y[k+1] = Y[k] + rnd.Walk();
			Z[k+1] = Z[k] + rnd.Walk();
		}
	}

	//computation of the square radiuses: ordered by number of steps
	dist(X,Y,Z,r2,N,M);

	//averaging the sq. radiuses in groups of N (data blocking)
	Blocking RW(M*N,N);
	RW.CAvgs(r2);
	RW.CStDev();
	RW.Output("RWdiscrete.dat");


	//RANDOM WALK ON 3D CONTINUUM

	double theta, phi;


	for(int i=0;i<M;i++){
		X[N*i] = 0;
		Y[N*i] = 0;
		Z[N*i] = 0;
		for(int j=0;j<N-1;j++){
			phi = 2*M_PI*rnd.Rannyu();
			theta = M_PI*rnd.Rannyu();
			int k = N*i+j;
			X[k+1] = X[k] + sin(theta)*cos(phi);
			Y[k+1] = Y[k] + sin(theta)*sin(phi);
			Z[k+1] = Z[k] + cos(theta);
		}
	}

	dist(X,Y,Z,r2,N,M);

	RW.CAvgs(r2);
	RW.CStDev();
	RW.Output("RWcont.dat");

	rnd.SaveSeed();

	return 0;
}


void dist(double *X, double *Y, double *Z, double*r2, int N, int M){
	for(int j=0;j<N;j++){
		for(int i=0;i<M;i++){
			int k = N*i+j;
			int l = M*j+i;
			r2[l] = pow(X[k],2)+pow(Y[k],2)+pow(Z[k],2);
		}
	}
}
