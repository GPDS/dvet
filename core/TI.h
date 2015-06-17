#ifndef TI_H_
#define TI_H_

#include "Video.h"
#include "TemporalMap.h"

class TI {
	public:
		void computeTI(Video, Video, TemporalMap,int, int );
		double getTI();


	private:
		double TI_Avg;
};

#endif /* TI_H_ */
