#include <iostream>
#include <fstream>
#include <cmath>
#include "blocking.h"
#include "random.h"
#include "print.h"

using namespace std;

double max(double a , double b ){
    if (a>=b) return a;
    else return b;
}

int main(){
    Random rnd;
    rnd.LoadSeed("Primes","seed.in");//Setting up the generator

    int M = 10000;
    double S0 = 100;    //initial asset price
    double t = 1;       //delivery time
    double K = 100;     //strike price
    double r = 0.1;      //risk-free interest rate
    double sigma = 0.25;//volatility

    double* S = new double[M];
    double* call = new double[M];
    double* put = new double[M];


    Blocking *blk = new Blocking(M,100);

    //sampling directly the final asset price
    for(int i=0;i<M;i++){
        S[i] = S0*exp((r-0.5*sigma*sigma)*t+sigma*rnd.Gauss(0,t));
        call[i] = max(0,S[i]-K);
        put[i] = max(0,K-S[i]);
        //cout<<S[i]<<"\t"<<call[i]<<"\t"<<put[i]<<endl;
    }

    blk->CAvgs(call);
    blk->CStDev();
    blk->Output("call_dir.dat");

    blk->CAvgs(put);
    blk->CStDev();
    blk->Output("put_dir.dat");


    // DISCRETE SAMPLING
    int N = 100; // # of time points

    for(int i=0;i<M;i++){
        double s =  S0;
        //recursive relation:
        for(int j=0;j<N;j++){
            //cout<<s<<"\t";
            s = s*exp((r-0.5*sigma*sigma)*t/N+sigma*rnd.Gauss(0,1)*sqrt(t/N));
        }
        //cout<<s<<endl;
        S[i] = s;

        call[i] = max(0,S[i]-K);
        put[i] = max(0,K-S[i]);

    }

    blk->CAvgs(call);
    blk->CStDev();
    blk->Output("call_disc.dat");

    blk->CAvgs(put);
    blk->CStDev();
    blk->Output("put_disc.dat");

    rnd.SaveSeed();
    return 0;
}
