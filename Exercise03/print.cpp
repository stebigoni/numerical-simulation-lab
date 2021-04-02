#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void print_to_file(double *data, int Nrows, int Ncols, string fname){
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

void print_to_file(int* data, int Nrows, int Ncols, string fname){
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

void print_to_file(double *data, int N, string fname){
	print_to_file(data,N,0,fname);
}
