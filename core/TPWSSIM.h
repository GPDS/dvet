#ifndef TPWSSIM_H_
#define TPWSSIM_H_

#include "Video.h"
#include "Sobel.h"
#include "TemporalMap.h"
#include "TI.h"
#include "SI.h"
#include "PWSSIM.h"

class TPWSSIM {
	public:
		void computeTPWSSIM(Video, Video, Sobel,int, int);
		void computeTPVQI(TemporalMap, TemporalMap, Video, Video,Video,Video,Sobel,int ,int);
		double getTPWSSIM();
		double getTPVQI();
		void writeResultsInFile();

	private:
		double AverageTPWSSIM;
		double AverageTPVQI;
};

#endif /* TPWSSIM_H_ */
