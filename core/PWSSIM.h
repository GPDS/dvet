#ifndef PWSSIM_H
#define PWSSIM_H

#include "Sobel.h"
#include "Video.h"

class PWSSIM {

	public:
		void computePWSSIM(Video, Video, Sobel, int, int);
		double getPWSSIM();
		void writeResultsInFile();
	
	private:
		double PWSSIM;
		long t0,t;
		double deltat;

};
#endif
