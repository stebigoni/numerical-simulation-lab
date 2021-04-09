#include<iostream>
#include<cmath>
#include<string>
#include<iterator>
#include"blocking.h"

using namespace std;

Blocking::Blocking(int M, int N){
    _M = M;
    _N = N;
    _L = M/N;
}

Blocking::~Blocking(){
    delete[] m;
    delete[] m2;
    delete[] cm;
    delete[] cm2;
    delete[] err;
}

void Blocking::Avgs(double r[]){
    //computes block means and square means
    m   = new double[_N];
    	if(!m){
    		cout<<"ALLOCATION ERROR"<<endl;
    		exit(1);
    	}
    m2  = new double[_N];
    	if(!m2){
    		cout<<"ALLOCATION ERROR"<<endl;
    		exit(1);
    	}
    for(i=0;i<_N;i++){
        sum=0;
        for(j=0;j<_L;j++){
            k = j+i*_L;
            sum+= r[k]; //sums all numbers in block
        }
        m[i] = 1.*sum/(_L);
        m2[i] = m[i]*m[i];
    }
}

void Blocking::CAvgs(double r[]){
	this->Avgs(r);
    	cm  = new double[_N];
      	if(!m){
    		cout<<"ALLOCATION ERROR"<<endl;
    		exit(1);
    	}
	cm2 = new double[_N];
	for(i=0;i<_N;i++){
	  cm[i]=0;
	  cm2[i]=0;
	  for(j=0;j<i+1;j++){
	      cm[i] += m[j];      //adds to m[i] all i preceding blocks' means
	      cm2[i] += m2[j];    //adds  "  "   "         "     square means
	  }
	  cm[i]/=(i+1);
	  cm2[i]/=(i+1);
	}
}

void Blocking::CErrs(){
    //computes (cumulative) std deviations
    if(cm == NULL) cerr<<"Error: cumulative means not calculated";
    else{
      err = new double[_N];
      err[0] = 0;
      for(i=1;i<_N;i++) {
          err[i] = sqrt( (cm2[i]-pow(cm[i],2))/i );
      }
    }
}


double *Blocking::ChiSq(double *r, int m){
	
}


double *Blocking::GetAvgs(){
    return m;
}

double *Blocking::GetCAvgs(){
    return cm;
}

double *Blocking::GetCErrs(){
    return err;
}

void Blocking::Output(string fname){
    out.open(fname);
     if (out.is_open()){
    	out<<_M<<endl; //first line is M
    	for(int i=0; i<_N; i++) out<<cm[i]<<" \t"<<err[i]<<endl;
    	out.close();
    }
    else cerr<<"ERROR: unable to open "<<fname<<endl;
}
