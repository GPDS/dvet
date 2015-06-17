#include "PSNR.h"


void PSNR::computePSNR(Video RefVideo, Video TestVideo,int row,int col)
{
    t0 = clock();

    int i=0,j=0, N=0;
		int MaxPixelValue = 255;
    int Noframes = RefVideo.returnFrames();
    int Nopixels = row*col;

    double MSE = 0;

    for(N = 0; N < Noframes; N++)
    {

        RefVideo.readVideo(N,row,col);

        TestVideo.readVideo(N,row,col);

        for(i = 0; i < col; i++)
        {
        	for(j = 0;j<row;j++)
            MSE += pow ((RefVideo.get_Y_Ptrstream(N,j,i) - TestVideo.get_Y_Ptrstream(N,j,i)) ,2);

        }
    }

    MSE /= (i*j*N);
    if(PSNR>100)
        PSNR = 100;
    PSNR = 10*log10(pow(MaxPixelValue,2)/MSE);




    t1 = clock();
    deltat = (t1 - t0)/CLOCKS_PER_SEC;
}

double PSNR::getPSNR()
{
    return PSNR;
}

void PSNR::writeResultsInFile()
{
    FILE *fp, *ft;

    char objectiveResults[30] = "psnr.txt", timeResults[30] = "psnr_timeexec.txt";

    if(!(fp = fopen(objectiveResults,"a+")) || !(ft = fopen(timeResults,"a+")))
    {
        printf("\nErro: Não foi possível criar os arquivos de saída para os resultados.");
        exit(1);
    }
    fprintf(fp, "%lf\n", getPSNR());
    fprintf(ft, "%lf\n", deltat);
}
