#include "Sobel.h"
#include "TPWSSIM.h"
#include "SSIM.h"

int main(){

    Video ref,teste,ref1,teste1;
		Image reserva1,reserva2;
		TPWSSIM tpwssim;
		TemporalMap refvideo, testvideo;
		Sobel refsobel;
		long nFrames,nPixels;
		int col,row,j;

		row = 352;
		col = 288;
		
		float coefs[3] = {2,2,1.5};
				ref.setCoefs(coefs);
		ref.OpenFile("akiyo_cif.yuv",row,col);
				ref1.setCoefs(coefs);

		ref1.OpenFile("akiyo_cif.yuv",row,col);
		teste.setCoefs(coefs);
		teste.OpenFile("akiyo_cif.yuv",row,col);
		teste1.setCoefs(coefs);
		teste1.OpenFile("akiyo_cif.yuv",row,col);


		tpwssim.computeTPVQI(refvideo,testvideo,ref,teste,ref1,teste1,refsobel,row,col);
		tpwssim.computeTPWSSIM(ref,teste,refsobel,row,col);
		tpwssim.writeResultsInFile();
			ref.DeallocFrame();
			teste.DeallocFrame();
			ref1.DeallocFrame();
			teste1.DeallocFrame();


return 0;
}	
