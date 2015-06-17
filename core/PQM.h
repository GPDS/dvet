#ifndef PQM_H_
#define PQM_H_

#include "Video.h"

class PQM
{
	public:
		void computePQM(Video, Video,int, int);
		double getPQM();
		void writeResultsInFile();

	private:
	
		double PQM;
};

#endif /* PQM_H_ */
