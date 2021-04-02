#ifndef _blocking_
#define _blocking_
#include<string>
#include<fstream>

using namespace std;

	class Blocking{
		public:
			Blocking(int, int); //constructor: (#steps,#blocks)
			~Blocking(); 		//destructor

			void Avgs(double*); //calculates single block averages of input
			void CAvgs(double*);//calculates cumulative averages of input for each block
			void Errs();		//calculates cumulative errors of Avgs result

			double *GetAvgs();
			double *GetCAvgs();
			double *GetErrs();

			void Output(string);//outputs avgs and errs

		private:
			double *m 	= NULL;
			double *m2 	= NULL;
			double *cm 	= NULL;
			double *cm2	= NULL;
			double *err = NULL;
			double sum;
			int _M,_N,_L,i,j,k;
			ofstream out;
};






#endif
