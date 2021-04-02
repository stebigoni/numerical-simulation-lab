#include<iostream>
#include<cmath>
#include<string>
#include<iterator>
#include"blocking.h"

using namespace std;

Blocking::Blocking(int M, int N){
    _M = M;   //total # of steps
    _N = N;                 //# of blocks
    _L = _M/N;              //# steps per block
    m   = new double[N];
    m2  = new double[N];
    cm  = new double[N];
    cm2 = new double[N];
    err = new double[N];

}

Blocking::~Blocking(){
    delete[] m;
    delete[] m2;
    delete[] cm;
    delete[] cm2;
    delete[] err;
}

void Blocking::Avgs(double r[]){
    //single block mean and square mean
    for(i=0;i<_N;i++){
        sum=0;
        for(j=0;j<_L;j++){
            k = j+i*_L;
            sum+= r[k]; //sums all numbers in block
        }
        m[i] = sum/double(_L);
        m2[i] = m[i]*m[i];
    }
}



void Blocking::CAvgs(double r[]){

    this->Avgs(r);
    for(i=0;i<_N;i++){
        //cumulative mean and square mean
        cm[i]=0;
        cm2[i]=0;
        for(j=0;j<i+1;j++){
            cm[i] += m[j];      //sums all preceding blocks' mean
            cm2[i] += m2[j];    //sums     "   "           square mean
        }
        cm[i]/=(i+1);
        cm2[i]/=(i+1);
    }
}

void Blocking::Errs(){
    err[0] = 0;
    for(i=1;i<_N;i++) {
        err[i] = sqrt( (cm2[i]-pow(cm[i],2))/i );
    }
}

double *Blocking::GetAvgs(){
    return m;
}

double *Blocking::GetCAvgs(){
    return cm;
}

double *Blocking::GetErrs(){
    return err;
}

void Blocking::Output(string fname){
    out.open(fname);
     if (out.is_open()){

    	out<<_M<<endl;
    	for(int i=0; i<_N; i++) out<<cm[i]<<" "<<err[i]<<endl;
    	out.close();
    }
    else cerr<<"ERROR: unable to open "<<fname<<endl;
}
