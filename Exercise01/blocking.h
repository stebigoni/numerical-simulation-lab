/****************************************************************
**** This library contains tools for data blocking,	*********
**** i.e. dividing large data arrays in  blocks		*********
**** to compute various statistical properties.	 	*********
**** Stefano Bigoni, 2020/2021				*********
****************************************************************/
#ifndef _blocking_
#define _blocking_
#include<string>
#include<fstream>

using namespace std;

	class Blocking{
		public:
			Blocking(int, int); //constructor: (#steps,#blocks)
			~Blocking(); 		//destructor

			void Avgs(double*); 	//calculates single block averages of input
			void CAvgs(double*);	//calculates single then cumulative block averages of input
			void CErrs();		//calculates cumulative errors of Avgs result (after CAvgs has been used)
			
			double *ChiSq(double*,int);	//calculates the chi squared (uniform distribution in [0,1], given # of bins) for each block
			
			double *GetAvgs();
			double *GetCAvgs();
			double *GetCErrs();

			void Output(string);//outputs avgs and errs

		private:
			double *m 	= NULL; // block means
			double *m2 	= NULL; // block squared means
			double *cm 	= NULL; // block cumulative means
			double *cm2	= NULL; // block cumulative square means
			double *err = NULL; // block standard deviations
			double sum;	// auxiliary variable
			int _M; // # of elements in array
			int _N; // # of blocks
			int _L; //# of elements in single block
			int i,j,k; // indices
			ofstream out; //
};






#endif
