#ifndef SI_H
#define SI_H


#include "Video.h"
#include "Sobel.h"
class SI{

	public:
		void ComputeSI(Video,Sobel,int,int);
		double get_SI();
		void writeSI();

	private:
	 	double SI_avg;


};
#endif
