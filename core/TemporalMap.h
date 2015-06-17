#ifndef TEMPORALMAP_H_
#define TEMPORALMAP_H_

#include "Video.h"


class TemporalMap{


	public:
		void generateTemporalMap(Image, Image);
		void writeFrames(int, int, int);
    void allocate_Pixelmaps(int, int,float coefs[]);
    void deallocate_Pixelmaps();
    int get_TemporalMap_Ptrstream(int ,int);

	private:
		Image temporalMap;

};
#endif
