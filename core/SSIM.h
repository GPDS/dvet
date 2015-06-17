#ifndef SSIM_H
#define SSIM_H

#include "Video.h"


class SSIM
{
    public:
        void computeSSIM(Video, Video,int,int);
        double getSSIM();
        void writeResultsInFile();
//        void SSIM();
    protected:

    private:
			double SSIM;
			long t0,t;
			double deltat;
};

#endif // SSIM_H
