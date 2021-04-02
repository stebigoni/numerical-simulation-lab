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
    csd  = new double[N];

}

Blocking::~Blocking(){
    delete[] m;
    delete[] m2;
    delete[] cm;
    delete[] cm2;
    delete[] csd;
}

void Blocking::Avgs(double r[]){
    //single block mean and square mean
    double sum;
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

void Blocking::Avgs(int r[]){
    //single block mean and square mean
    int sum;
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

void Blocking::CAvgs(int r[]){
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


void Blocking::CStDev(){
    csd[0] = 0;
    for(i=1;i<_N;i++) {
        csd[i] = sqrt( (cm2[i]-pow(cm[i],2))/i );
    }
}

double *Blocking::GetAvgs(){
    return m;
}

double *Blocking::GetAvgs2(){
    return m2;
}

double *Blocking::GetCAvgs(){
    return cm;
}

double *Blocking::GetCAvgs2(){
    return cm2;
}

double *Blocking::GetCStDev(){
    return csd;
}

void Blocking::Output(string fname){
    out.open(fname);
     if (out.is_open()){

    	out<<_M<<endl;
    	for(int i=0; i<_N; i++) out<<cm[i]<<" "<<csd[i]<<endl;
    	out.close();
    }
    else cerr<<"ERROR: unable to open "<<fname<<endl;
}
