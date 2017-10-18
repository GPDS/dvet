#ifndef PWSSIM_H
#define PWSSIM_H

using namespace std;

class PWSSIM {

	public:
		void computePWSSIM(Video& RefVideo, Video& TestVideo, int row, int col);
		double getPWSSIM();
		void writeResultsInFile();
	
	private:
		double PWSSIM;
		long t0,t;
		double deltat;

};
#endif
