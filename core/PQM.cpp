#include "PQM.h"


void PQM::computePQM(Video RefVideo, Video TestVideo,int row ,int col)
{
	double avg_Ref = 0, avg_Test = 0, std_Ref = 0, std_Test = 0, cov_RefTest = 0;

	double alpha = 0, alpha_tmp = 0, C = 0,PDM = 0,  W = 0, sum_W = 0;

	int Noframes = RefVideo.returnFrames();
	int Nolines = row;
	int Nocols = col;
	int MaxPixelValue = 255;
	int N,i,j,k,n, pos = 0, b = 8;

	for(N = 0; N < Noframes; N++)
	{
		RefVideo.readVideo(N,row,col);
		TestVideo.readVideo(N,row,col);

		for(i = 0; i < Nolines; i += b)
		{
			for(j = 0; j < Nocols; j +=b)
			{
                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
						avg_Ref += RefVideo.get_Y_Ptrstream(N,k,n);
						avg_Test += TestVideo.get_Y_Ptrstream(N,k,n);
					}
				avg_Ref /= (b*b);

				avg_Test /= (b*b);


				if(avg_Ref <= 1 && avg_Test <= 1)
				{
					alpha += 0;
				}
				else if(avg_Ref <= 1 && avg_Test >= 1)
				{
					alpha += 1;
				}
				else
				{
                    for(n = j; n < (j+b); n++)
					{
                        for(k = i; k < (i+b); k++)
						{
							//pos = n + k*Nocols;
								alpha_tmp = pow(RefVideo.get_Y_Ptrstream(N,k,n) - TestVideo.get_Y_Ptrstream(N,k,n),4)/ pow(avg_Ref,2);

								if(alpha_tmp > 1)
									alpha_tmp = 1;

								alpha += alpha_tmp;
							}
						}
					}
				}

				alpha /= (b*b);

                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
							std_Ref += pow((RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref),2);

					}
				std_Ref /= (b*b-1);

				std_Test /= (b*b-1);

                for(n = j; n < (j+b); n++)
                    for(k = i; k < (i+b); k++)
					{
						cov_RefTest += (RefVideo.get_Y_Ptrstream(N,k,n) - avg_Ref)*(TestVideo.get_Y_Ptrstream(N,k,n) - avg_Test);
					}

				cov_RefTest /= (b*b-1);

				C = 1 + (pow((std_Ref - std_Test),2) + MaxPixelValue)/(pow(std_Ref,2) + pow(std_Test,2) - 2*pow(cov_RefTest,2) + MaxPixelValue);


				if(!avg_Ref)
				{
					W = 1;
				}
				else
				{
					W = MaxPixelValue/avg_Ref;
				}

				sum_W += W;


				PDM += W*C*alpha;


				avg_Ref = 0; avg_Test = 0;
			    std_Ref = 0;  std_Test = 0;
			    cov_RefTest = 0;
				alpha = 0; alpha_tmp = 0;
				C = 0;
				W = 0;
			}
		}


	PDM /= sum_W;


	if(1 - PDM < 0)
		PDM = 0;
	else
	{
		PDM = 1 - PDM;
	}




	PQM = PDM;


}

double PQM::getPQM()
{
	return PQM;
}

void PQM::writeResultsInFile()
{
    FILE *fp;



    if(!(fp = fopen("PQM.txt","a+")))
    {
        printf("\nErro: Não foi possí­vel criar os arquivos de saí­da para os resultados.");
        exit(1);
    }

    fprintf(fp, "%lf\n", getPQM());
}
