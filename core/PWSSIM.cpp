#include "PWSSIM.h"

void PWSSIM::computePWSSIM(Video RefVideo, Video TestVideo, Sobel RefSobel, int row, int col)
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
	float coefs[3];
	Image teste;

	int Noframes = RefVideo.returnFrames();
	int Nolines= row;
	int Nocols = col;

	int N=0, i=0, j=0, k=0, n=0, b=8;

	RefVideo.getCoefs(coefs);
	teste.setCoefs(coefs);
	RefSobel.allocate_Pixelmaps(row,col,coefs);

	for(N = 0; N < Noframes; N++)
	{
		RefVideo.readVideo(N,row,col);


		teste=RefVideo.getFrame(N);

		TestVideo.readVideo(N,row,col);

		RefSobel.Sobel_Operation(teste);

		for(i = 0; i < Nolines; i += b)
			for(j = 0; j < Nocols; j += b)
			{
                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{

						avg_Ref += RefVideo.get_Y_Ptrstream(N,k,n);

						avg_Test += TestVideo.get_Y_Ptrstream(N,k,n);

						avg_Ref_sobel += RefSobel.get_Sobel_Ptrstream(k,n);



					}
					avg_Ref /= (b*b);

						avg_Test /= (b*b);

						avg_Ref_sobel /= (b*b);


                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
						std_Ref += pow((RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref),2);

						std_Test += pow((TestVideo.get_Y_Ptrstream(N,k,n) - avg_Test),2);

						std_Ref_sobel += pow((RefSobel.get_Sobel_Ptrstream(k,n) - avg_Ref_sobel),2);

					}
					std_Ref  = sqrt(std_Ref/(b*b-1));

					std_Test = sqrt(std_Test/(b*b-1));

					std_Ref_sobel = sqrt(std_Ref_sobel/(b*b-1));

					total_std_Ref_sobel += std_Ref_sobel;


                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{


						cov_RefTest += (RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref)*(TestVideo.get_Y_Ptrstream(N,k,n) - avg_Test);
					}


					cov_RefTest /= (b*b-1);



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
	RefSobel.deallocate_Pixelmaps();



	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;

}
void PWSSIM::writeResultsInFile()
{
    FILE *fp, *ft;

    char objectiveResults[30] = "pwssim_b24.txt", timeResults[30] = "pwssim_timeexec.txt";

    if(!(fp = fopen(objectiveResults,"a+")) || !(ft = fopen(timeResults,"a+")))
    {
        printf("\nErro: Não foi possível criar os arquivos de saída para os resultados.");
        exit(1);
    }
    fprintf(fp, "%lf\n", getPWSSIM());
    fprintf(ft, "%lf\n", deltat);
}
double PWSSIM::getPWSSIM()
{
	return PWSSIM;
}

