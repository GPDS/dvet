#include "SSIM.h"


void SSIM::computeSSIM(Video RefVideo, Video TestVideo, int row, int col)
{
	t0 = clock();
    SSIM =0;
	double C1 = 6.5025, C2 = 58.5225,
		   avg_Ref = 0, avg_Test = 0,
		   std_Ref = 0, std_Test = 0,
		   cov_RefTest = 0;
	Image teste;
	int Noframes = RefVideo.returnFrames();
	int Nolines = row;
	int Nocols = col ;
	int N=0, i=0, j=0, k=0, n=0, b=8;
	int Noblocks = (Noframes)*(Nolines)*(Nocols)/(b*b);
	for(N = 0; N < Noframes; N++)
	{
		RefVideo.readVideo(N,row,col);
		TestVideo.readVideo(N,row,col);

		for(i = 0; i < Nolines; i += b)
			for(j = 0; j < Nocols; j += b)
			{
                for(n = j; n < (j+b); n++)
				for(k = i; k < (i+b); k++)
					{

						avg_Ref += RefVideo.get_Y_Ptrstream(N,k,n);

						avg_Test += TestVideo.get_Y_Ptrstream(N,k,n);

					}
				avg_Ref /= (b*b);

				avg_Test /= (b*b);
                for(n = j; n < (j+b); n++)
				for(k = i; k < (i+b); k++)

					{


						std_Ref += pow((RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref),2);

						std_Test += pow((TestVideo.get_Y_Ptrstream(N,k,n) - avg_Test),2);




					}
					std_Ref  = sqrt(std_Ref/(b*b-1));

					std_Test = sqrt(std_Test/(b*b-1));




                	for(n = j; n < (j+b); n++)
				for(k = i; k < (i+b); k++)

                    {
						cov_RefTest += (RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref)*(TestVideo.get_Y_Ptrstream(N,k,n) - avg_Test);
					}


					cov_RefTest /= (b*b-1);

					SSIM += (((2*avg_Ref*avg_Test + C1)*(2*cov_RefTest + C2))/
							  ((avg_Ref*avg_Ref + avg_Test*avg_Test + C1)*(std_Ref*std_Ref + std_Test*std_Test + C2)));



					avg_Ref = 0;  avg_Test = 0;
					std_Ref = 0;  std_Test = 0;
					cov_RefTest = 0;

			}
	}

	SSIM /= Noblocks;




	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;

}
void SSIM::writeResultsInFile()
{
    FILE *fp, *ft;

    char objectiveResults[30] = "ssim_b20.txt", timeResults[30] = "ssim_timeexec.txt";

    if(!(fp = fopen(objectiveResults,"a+")) || !(ft = fopen(timeResults,"a+")))
    {
        printf("\nErro: Não foi possível criar os arquivos de saída para os resultados.");
        exit(1);
    }
    fprintf(fp, "%lf\n", getSSIM());
    fprintf(ft, "%lf\n", deltat);
}
double SSIM::getSSIM()
{
	return SSIM;
}

