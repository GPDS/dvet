#include "main.h"


void PSNR::computePSNR(Video &RefVideo, Video &TestVideo,int row,int col)
{ 
    t0 = clock();

    int i=0,j=0, N=0;
	int maxPixelValue = 255;
    int noFrames = RefVideo.returnFrames();
    int noPixels = row*col;

    double MSE = 0;

    for(N = 0; N < noFrames; N++)
    {

        RefVideo.readVideo(N,row,col);

        TestVideo.readVideo(N,row,col);
        for(i = 0; i < col; i++)
        {
        	for(j = 0;j<row;j++)
            MSE += pow ((int)(RefVideo.getPtrstream_Y(i,j) - TestVideo.getPtrstream_Y(i,j)) ,2);
        }
    }

 	
    MSE /= (i*j*N);
    

    PSNR = 10*log10(pow(maxPixelValue,2)/MSE);
	if(PSNR>100)
        PSNR = 100;

    t1 = clock();
    deltat = (t1 - t0)/CLOCKS_PER_SEC;
}

double PSNR::getPSNR()
{
    return PSNR;
}

void PSNR::writeResultsInFile()
{

	ofstream Name("store/PSNR.txt", ios::app);
	ofstream time_exec("store/PSNR_Timeexec.txt",ios::app);
	if (!Name || !time_exec)
		cout << "File couldn't open" << endl;
	else
	{
		Name << getPSNR() << endl;
		time_exec << deltat << endl;
		Name.close();
		time_exec.close();	
	}
}
