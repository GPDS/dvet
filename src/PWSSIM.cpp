#include "main.h"

void PWSSIM::computePWSSIM(Video& RefVideo, Video& TestVideo,  int row, int col)
{

	t0 = clock();
    PWSSIM = 0;
	double C1 = 6.5025, C2 = 58.5225,
		   avg_Ref = 0, avg_Test = 0,
		   std_Ref = 0, std_Test = 0,
		   cov_RefTest = 0;

	double avg_Ref_sobel = 0,
		   std_Ref_sobel = 0,
		   total_std_Ref_sobel = 0;
	int coefs[2];
	Image test;
	Sobel RefSobel;
	int noFrames = RefVideo.returnFrames();
	int noLines= row;
	int noCols = col;

	int blocks=8;


	RefVideo.getCoefs(coefs);
	test.setCoefs(coefs[0], coefs[1]);
	RefSobel.allocatePixelMap(row,col,coefs[0], coefs[1]);

	for(int N = 0; N < noFrames; N++)
	{
		RefVideo.readVideo(N,row,col);


		test=RefVideo.getFrame();

		TestVideo.readVideo(N,row,col);
		RefSobel.Sobel_Operation(test);

		for(int line = 0; line < noLines; line += blocks)
			for(int column = 0; column < noCols; column += blocks)
			{
                for(int i = column; i < (column+blocks); i++)
                    for(int j = line; j < (line+blocks); j++)
					{

						avg_Ref += RefVideo.getPtrstream_Y(i,j);

						avg_Test += TestVideo.getPtrstream_Y(i,j);

						avg_Ref_sobel += RefSobel.get_Sobel_Ptrstream(i,j);

					}
					avg_Ref /= (blocks*blocks);

						avg_Test /= (blocks*blocks);

						avg_Ref_sobel /= (blocks*blocks);


                for(int i = column; i < (column+blocks); i++)
                    for(int j = line; j < (line+blocks); j++)
					{
						std_Ref += pow((RefVideo.getPtrstream_Y(i,j) - avg_Ref),2);

						std_Test += pow((TestVideo.getPtrstream_Y(i,j) - avg_Test),2);

						std_Ref_sobel += pow((RefSobel.get_Sobel_Ptrstream(i,j) - avg_Ref_sobel),2);

					}

					std_Ref  = sqrt(std_Ref/(blocks*blocks-1));

					std_Test = sqrt(std_Test/(blocks*blocks-1));

					std_Ref_sobel = sqrt(std_Ref_sobel/(blocks*blocks-1));

					total_std_Ref_sobel += std_Ref_sobel;


                for(int i = column; i < (column+blocks); i++)
                    for(int j = line; j < (line+blocks); j++)
					{
						cov_RefTest += (RefVideo.getPtrstream_Y(i,j) - avg_Ref)*(TestVideo.getPtrstream_Y(i,j) - avg_Test);
					}


					cov_RefTest /= (blocks*blocks-1);



					PWSSIM += (((2*avg_Ref*avg_Test + C1)*(2*cov_RefTest + C2))/
							  ((avg_Ref*avg_Ref + avg_Test*avg_Test + C1)*(std_Ref*std_Ref + std_Test*std_Test + C2)))*std_Ref_sobel;

					avg_Ref = 0;  avg_Test = 0;
					std_Ref = 0;  std_Test = 0;
					cov_RefTest = 0;
					avg_Ref_sobel = 0;
					std_Ref_sobel = 0;
			}

	}

	PWSSIM /= total_std_Ref_sobel;
	RefSobel.deallocatePixelMap();



	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;

}
void PWSSIM::writeResultsInFile()
{
    ofstream Name("store/PWSSIM.txt", ios::app);
    ofstream time_exec("store/PWSSIM_Timeexec.txt", ios::app);
    
    if(!Name || !time_exec)
    	cout << "The file couldn't open" << endl;
    	
    else
    {
    	Name << getPWSSIM() << endl;
    	time_exec << deltat<< endl;
    	Name.close();
    	time_exec.close();
    }
}
double PWSSIM::getPWSSIM()
{
	return PWSSIM;
}
