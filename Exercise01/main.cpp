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
	for(int i=0;i<M;i++){
		sigma2[i] = pow(r[i]-0.5,2);
	}

	//estimation of <sigma^2>
	blk.CAvgs(r);
	blk.CErrs();
	blk.Output("output2.dat");

	//estimation of chi squared
	double *chi2 = new double[N];
	int m = 100; // # of bins
	chi2 = blk.ChiSq(r,m);
	printfile(chi2,m,"chi2.dat");
		

	/************************ Exercise 01.2*************************/
	
	int K = 10000;	//# of measurements
	int n = 4;	//# of different experiments

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
	
	// Generation of M random values for the cosine of angle theta (in [0, pi/2]), with kind-of-uniform distribution
	double *cos_theta = new double[M];
	double *events = new double[M];
	double l = 0.5; //length of the needle (d=1)
	
	for(int i=0;i<M;i++){
		cos_theta[i] = rnd.Circ();
		//for the spatial coordinate I use the M values previously generated and stored in r[]
	double y2 = r[i] + l/2*cos_theta[i];
	double y1 = r[i] - l/2*cos_theta[i];
		if(y1<0 || y2<0 || y1>1 || y2>1){
			events[i] = 1;
		}
		else events[i] = 0;
	}
	
	printfile(cos_theta,10000,"cos.dat");
	
	blk.CAvgs(events);
	blk.CErrs();
	blk.Output("events.dat");
	
	//append the value of l to the events file
	ofstream outf;
	outf.open("events.dat",ios_base::app);
	outf<<l<<"\t nan"<<endl;
	outf.close();
	
	
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
