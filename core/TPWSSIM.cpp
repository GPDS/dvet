#include "TPWSSIM.h"
void TPWSSIM::computeTPWSSIM(Video RefVideo, Video TestVideo, Sobel RefSobel,int row, int col)
{
	PWSSIM pwssim;

	pwssim.computePWSSIM(RefVideo, TestVideo, RefSobel,row,col);

	AverageTPWSSIM = (pwssim.getPWSSIM() + AverageTPVQI)*0.5;
	printf("\nPWSSIM: %lf\nTPVQI: %lf\n", pwssim.getPWSSIM(), AverageTPVQI);
}

void TPWSSIM::computeTPVQI(TemporalMap RefTempMap, TemporalMap TestTempMap, Video RefVideo, Video TestVideo, Video RefVideo0, Video TestVideo0, Sobel RefSobel,int row, int col)
{
	double TPVQI = 0;

	double C1 = 6.5025, C2 = 58.5225,
		   avg_Ref = 0, avg_Test = 0,
		   std_Ref = 0, std_Test = 0,
		   cov_RefTest = 0;

	double avg_Ref_sobel = 0,
		   std_Ref_sobel = 0,
		   total_std_Ref_sobel= 0;

	int Noframes = RefVideo.returnFrames();
	int Nolines = row;
	int Nocols = col;
	float coefs[3];

	Image ref, ref1, test, test1;

	int N=0, i=0, j=0, k=0, n=0, pos = 0, b = 8;

	RefVideo.getCoefs(coefs);
	RefSobel.allocate_Pixelmaps(row,col,coefs);
	RefTempMap.allocate_Pixelmaps(row,col,coefs);
	TestTempMap.allocate_Pixelmaps(row,col,coefs);

	for(N = 0; N < Noframes - 1; N++)
	{
		RefVideo.readVideo(N,row,col);
		RefVideo0.readVideo(N+1,row,col);
		TestVideo.readVideo(N,row,col);
		TestVideo0.readVideo(N+1,row,col);
		ref = RefVideo.getFrame(N);
		ref1 = RefVideo0.getFrame(N+1);
		test = TestVideo.getFrame(N);
		test1 = TestVideo0.getFrame(N+1);
		RefTempMap.generateTemporalMap(ref,ref1);
		TestTempMap.generateTemporalMap(test, test1);
		RefSobel.Sobel_Operation(ref);

		for(i = 0; i < Nolines; i += b)
			for(j = 0; j < Nocols; j += b)
			{
                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
							avg_Ref += RefTempMap.get_TemporalMap_Ptrstream(k,n);
							avg_Test += TestTempMap.get_TemporalMap_Ptrstream(k,n);
							avg_Ref_sobel += RefSobel.get_Sobel_Ptrstream(k,n);


					}

					avg_Ref /= (b*b);
					avg_Test /= (b*b);
					avg_Ref_sobel /= (b*b);

                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
							std_Ref += pow((RefTempMap.get_TemporalMap_Ptrstream(k,n) - avg_Ref),2);
							std_Test += pow((TestTempMap.get_TemporalMap_Ptrstream(k,n) - avg_Test),2);
							std_Ref_sobel += pow((RefSobel.get_Sobel_Ptrstream(k,n) - avg_Ref_sobel),2);
						}
					}

					std_Ref  = sqrt(std_Ref/(b*b-1));
					std_Test = sqrt(std_Test/(b*b-1));
					std_Ref_sobel = sqrt(std_Ref_sobel/(b*b-1));
					total_std_Ref_sobel += std_Ref_sobel;

                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
						if(k<Nolines-b && n <Nocols-b)
							cov_RefTest += (RefTempMap.get_TemporalMap_Ptrstream(k,n)- avg_Ref)*(TestTempMap.get_TemporalMap_Ptrstream(k,n) - avg_Test);
					}


					cov_RefTest /= (b*b-1);

						// TODO : Perguntar se C1 e C2 são necessários
					TPVQI += (((2*avg_Ref*avg_Test + C1)*(2*cov_RefTest + C2))/
							  ((avg_Ref*avg_Ref + avg_Test*avg_Test + C1)*(std_Ref*std_Ref + std_Test*std_Test + C2)))*std_Ref_sobel;

					avg_Ref = 0; avg_Test = 0;
					std_Ref = 0; std_Test = 0;
					cov_RefTest = 0;
					avg_Ref_sobel = 0;
					std_Ref_sobel = 0;
			}


	TPVQI /= total_std_Ref_sobel;


	AverageTPVQI = TPVQI;
}

double TPWSSIM::getTPWSSIM()
{
	return AverageTPWSSIM;
}

double TPWSSIM::getTPVQI()
{
	return AverageTPVQI;
}

void TPWSSIM::writeResultsInFile()
{
    FILE *fp;



    if(!(fp = fopen("TPWSSIMb24.txt","a+")))
    {
        printf("\nErro: Não foi possível criar os arquivos de saída para os resultados.");
        exit(1);
    }
    fprintf(fp, "%lf\n", getTPWSSIM());
}
