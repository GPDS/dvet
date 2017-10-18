#ifndef SSIM_H
#define SSIM_H

using namespace std;

class SSIM
{
    public:
        void computeSSIM(Video& RefVideo, Video& TestVideo, int row, int col);
        double getSSIM();
        void writeResultsInFile();
		//void SSIM();
    protected:

    private:
		double SSIM;
		long t0,t;
		double deltat;
};

#endif // SSIM_H
