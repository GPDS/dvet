#ifndef PSNR_H
#define PSNR_H

#include "Video.h"


class PSNR
{
    public:
       
        void computePSNR(Video, Video,int ,int);
        double getPSNR();
        void writeResultsInFile();
    protected:

    private:
        double PSNR;
        long t0; // Executions time of the method computePSNR();
        long t1;
        double deltat;
};

#endif // PSNR_H
