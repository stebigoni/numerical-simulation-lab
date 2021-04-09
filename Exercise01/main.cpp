/*******************************************
		NSL - EXERCISE 1
		Stefano Bigoni
*******************************************/
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

	int M = 1000000; 	//number of steps
	int N = 100;		//number of blocks
	double *r = new double[M]; //random numbers array
		//Check for correct allocation
		if (!r){ 
			cout<<"ALLOCATION ERROR"<<endl;
			exit(1);
		}
	
	//Constructing the blocking scheme
	Blocking blk(M,N); 	

	//Generating the M pseudo-random numbers
	for (int i=0; i<M; i++){
		r[i] = rnd.Rannyu();
	}

	//Estimation of <r>
	blk.CAvgs(r);
	blk.CErrs();
	blk.Output("output.dat");

	//calculating square errors
	double *sigma2 = new double[M];
		//Check for correct allocation
		if (!sigma2){ 
			cout<<"ALLOCATION ERROR"<<endl;
			exit(1);
		}
	for(int i=0;i<M;i++){
		sigma2[i] = pow(r[i]-0.5,2);
	}

	//estimation of <sigma^2>
	blk.CAvgs(r);
	blk.CErrs();
	blk.Output("output2.dat");

	//__________chisquare test____________
	{ 
	//scope opened for re-using variable names
		
		int m = 100; // # of bins
		int n[m]; // # of events in each bin
		int K = 100; // # of chi-squared values
		double chi2[100]; // array of chi-squared values
		int E = M/K/m; // expected value of successes for each bin (uniform distribution)
		
		for(int j=0; j<100; j++){
			// initializing the bins
			for(int i=0; i<m; i++) n[i]=0; 
			//histogram counting (M/K values at a time)
			for(int i=j*M/K;i<(j+1)*M/K;i++){
				int k = r[i]*100;
				n[k]++;
			}
			//chi square calculation
			chi2[j] = 0;
			for(int i=0;i<m;i++){ //sum
				chi2[j] += pow(n[i]-E,2);
			}
			chi2[j]/= E;
		}
		printfile(chi2,100,"chi2.dat");
	}
	
	/************************ Exercise 01.2*************************/
	
	int K = 10000;	//# of measurements
	int n = 4;	//# of different experiments

	//arrays containing the mean values
	double *mu = new double[K*4];
		//Check for correct allocation
		if (!mu){ 
			cout<<"ALLOCATION ERROR"<<endl;
			exit(1);
		}
	double *me = new double[K*4];
		//Check for correct allocation
		if (!me){ 
			cout<<"ALLOCATION ERROR"<<endl;
			exit(1);
		}
	double *ml = new double[K*4];
		//Check for correct allocation
		if (!ml){ 
			cout<<"ALLOCATION ERROR"<<endl;
			exit(1);
		}

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
	//output
	printfile(mu,K,n,"dice_unif.dat");
	printfile(me,K,n,"dice_exp.dat");
	printfile(ml,K,n,"dice_lor.dat");

	/************************ Exercise 01.3*************************/






	/*********** Final actions **************/
	
	delete[] r;
	delete[] sigma2;
	delete[] mu;
	delete[] me;
	delete[] ml;
	
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
	printfile(data,N,1,fname);
}
