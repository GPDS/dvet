#ifndef SOBEL_H
#define	SOBEL_H

#include "Video.h"

class Sobel {
    public:

				void writeFrames(int, int, int);
        void allocate_Pixelmaps(int row, int col,float coefs[]);
       void deallocate_Pixelmaps();
        void Sobel_Operation ( Image teste);
				int get_Sobel_Ptrstream(int ,int);
    private:
      
       Image sobel;

       
};

#endif	/* SOBEL_H */

