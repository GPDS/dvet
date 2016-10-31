#ifndef PSNR_H
#define PSNR_H

using namespace std;


class PSNR
{
    public:
       
        void computePSNR(Video &RefVideo, Video &TestVideo, int row, int col);
        double getPSNR();
        void writeResultsInFile();
    protected:

    private:
        double PSNR;
        long t0; // Executions time of the method computePSNR();
        long t1;
        double deltat;
};

#endif
