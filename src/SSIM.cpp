#include "common.h"
#include "Image.h"
#include "Video.h"
#include "SSIM.h"


void SSIM::computeSSIM(Video& RefVideo, Video& TestVideo, int row, int col)
{	
	t0 = clock();
    SSIM =0;
	double C1 = 6.5025, C2 = 58.5225,
		   avg_Ref = 0, avg_Test = 0,
		   std_Ref = 0, std_Test = 0,
		   cov_RefTest = 0;
	Image teste;
	int noFrames = TestVideo.returnFrames();
	int noLines = row;
	int noCols = col ;
	int blocks=8;
	int noBlocks = (noFrames)*(noLines)*(noCols)/(blocks*blocks);
	for(int N = 0; N < noFrames; N++)
	{
		RefVideo.readVideo(N,row,col);
		TestVideo.readVideo(N,row,col);


		for(int line = 0; line < noLines; line+= blocks)
			for(int column = 0; column < noCols; column+= blocks)
			{
                for(int i = column; i < (column+blocks); i++)
				for(int j = line; j < (line+blocks); j++)
				{
					avg_Ref += RefVideo.getPtrstream_Y(i,j);
					avg_Test += TestVideo.getPtrstream_Y(i,j);
				}
				avg_Ref /= (blocks*blocks);

				avg_Test /= (blocks*blocks);
                for(int i = column; i < (column+blocks); i++)
				for(int j = line; j < (line+blocks); j++)
				{
					std_Ref += pow((RefVideo.getPtrstream_Y(i,j) - avg_Ref),2);
					std_Test += pow((TestVideo.getPtrstream_Y(i,j) - avg_Test),2);
				}

				std_Ref  = sqrt(std_Ref/(blocks*blocks-1));
				std_Test = sqrt(std_Test/(blocks*blocks-1));

                for(int i = column; i < (column+blocks); i++)
				for(int j = line; j < (line+blocks); j++)
                {
					cov_RefTest += (RefVideo.getPtrstream_Y(i,j) - avg_Ref)*(TestVideo.getPtrstream_Y(i,j) - avg_Test);
				}

				cov_RefTest /= (blocks*blocks-1);
				
				SSIM += (((2*avg_Ref*avg_Test + C1)*(2*cov_RefTest + C2))/
							  ((avg_Ref*avg_Ref + avg_Test*avg_Test + C1)*(std_Ref*std_Ref + std_Test*std_Test + C2)));



				avg_Ref = 0;  avg_Test = 0;
				std_Ref = 0;  std_Test = 0;
				cov_RefTest = 0;

			}
	}

	SSIM /= noBlocks;

	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;
}

void SSIM::writeResultsInFile()
{
   	ofstream Name;
	ofstream time_exec("store/SSIM_Timeexec.txt",ios::app);
	Name.open("store/SSIM.txt", ios::app);
	
	
	if (!Name || !time_exec)
		cout << "The file couldn't open" << endl;

	else
	{
		Name << getSSIM() << endl;
		time_exec << deltat<< endl;
		Name.close();
		time_exec.close();	
	}	

}
double SSIM::getSSIM()
{
	return SSIM;
}
