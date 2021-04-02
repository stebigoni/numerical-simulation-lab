/********************************
		NSL - EXERCISE 1
		Stefano Bigoni
********************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "blocking.h"
using namespace std;

void printfile(double* data, int Nrows, int Ncols, string fname);
void printfile(double* data, int N, string fname);


int main (int argc, char *argv[]){

	/************************ Exercise 01.1*************************/

	Random rnd;
	rnd.LoadSeed("Primes","seed.in");//Setting up the generator

	int M = 100000; 	//number of steps
	int N = 100;		//number of blocks
	double r[M];		//random numbers array

	Blocking blk(M,N); 	//Constructing the blocking scheme

	//generating numbers
	for (int i=0; i<M; i++){
		r[i] = rnd.Rannyu();
	}

	//estimation of <r>
	blk.CAvgs(r);
	blk.Errs();
	blk.Output("output.dat");

	//estimation of <sigma^2>
	double sigma2[M];
	for(int i=0;i<M;i++){
		sigma2[i] = pow(r[i]-0.5,2);
	}
	blk.CAvgs(sigma2);
	blk.Errs();
	blk.Output("output2.dat");

	//chisquare test
	//int m = 100; //number of bin


	//Blocking chisquare(n,)
	/*
	double chi2[K];
	for(int i=0;i<K;i++){
		for(int j=0;j<n/K;i++){
			int k = j+i*n/K;

		}
		chi2[i] /=(n/K);
	}*/


	/************************ Exercise 01.2*************************/
	//setting up the experiment
	int K = 10000;	//# of measurements
	int n = 4;		//# of different experiments

	//arrays containing the mean values
	double *mu = new double[K*4];
	double *me = new double[K*4];
	double *ml = new double[K*4];

	int Nd[n] = {1,2,10,100}; //#s of throws

	for(int i=0;i<K;i++){
		for(int j=0;j<n;j++){
			mu[i*4+j]=0;	//initialization
			me[i*4+j]=0;
			ml[i*4+j]=0;
		}
		for(int j=0;j<n;j++){
			for(int k=0;k<Nd[j];k++){
				mu[i*n+j]+=rnd.Rannyu();
				me[i*n+j]+=rnd.Exp(1);
				ml[i*n+j]+=rnd.CauchyLorentz(0,1);
			}
			mu[i*n+j]/=double(Nd[j]);
			me[i*n+j]/=double(Nd[j]);
			ml[i*n+j]/=double(Nd[j]);
		}
	}


	Blocking blkdice(K,1);



	//output
	printfile(mu,K,n,"dice_unif.dat");
	printfile(me,K,n,"dice_exp.dat");
	printfile(ml,K,n,"dice_lor.dat");



	/************************ Exercise 01.3*************************/






	/*********** Final actions **************/

	rnd.SaveSeed(); //saving seed

	return 0;
}


void printfile(double *data, int Nrows, int Ncols, string fname){
	ofstream fout;
	fout.open(fname);
	if(fout.is_open()){
		for(int i=0;i<Nrows;i++){
			for(int j=0;j<Ncols;j++) fout<<data[i*Ncols+j]<<" ";
			fout<<endl;
		}
	}
	else cerr<<"ERROR: unable to open "<<fname<<endl;
}

void printfile(double *data, int N, string fname){
	printfile(data,N,0,fname);
}
