#include "TI.h"
#include "SSIM.h"
#include <cstdio>
#include "PWSSIM.h"
#include "Sobel.h"
		//For a 442 Video set d1=1, d2=2 and coef_mult = 2
		// For a 440 Video set d1=2 d2=2 and coef_mult = 1.5

int main(){

    Video ref,teste,ref1,teste1;
   //	TI aux;
    PWSSIM pwssim;
    Sobel sobel;
		float coefs[3] = {2,2,1.5};
        char name[20];

		int col,row,j;
		// Ajuste aqui o número de linhas e colunas do seu vídeo
		row = 768;
		col = 432;
        ref.setCoefs(coefs);
        ref.OpenFile("bs1_25fps.yuv",row,col);
        teste.setCoefs(coefs);
        int i =2;
		//Substitua o nome do arquivo no primeiro argumento

            sprintf(name,"bs%d_25fps.yuv",i);
            teste.OpenFile(name,row,col);
            pwssim.computePWSSIM(ref,teste,sobel,row,col);
            pwssim.writeResultsInFile();

		//Escreverá os resultados no arquivo psnr.txt e psnr_timeexec.txt


		ref.DeallocFrame();
		teste.DeallocFrame();

return 0;
}
