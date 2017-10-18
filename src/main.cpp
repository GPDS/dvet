#include "main.h"
#include <string.h>
#include <string>
using namespace std;
#define row 1920
#define col 1080

int main (int argc, char const* argv[]){

	Video reference,test;

	PSNR  psnr;
	SSIM ssim;
	PWSSIM pwssim;
	
	
	reference.setCoefs(2,2,row,col);
	reference.openFile("video.y4m",row,col);
	test.setCoefs(2,2,row,col);
	string entrada = "";
	
	test.openFile(argv[1],row,col);
	


	
	int numFrames = reference.returnFrames();


/**/
cout<< "Entrou na PSNR\n";
	//============= PSNR ==============
	psnr.computePSNR(reference,test,row,col);
	psnr.writeResultsInFile();
	

cout<< "\nEntrou na SSIM\n";
	//==============  SSIM  ===========
	ssim.computeSSIM(reference,test,row,col);
	ssim.writeResultsInFile();
	//=================================


cout<< "\nEntrou na PWSSIM\n";
	//==============  PWSSIM  ===========
	pwssim.computePWSSIM(reference,test,row,col);
	pwssim.writeResultsInFile();
	//=================================

	reference.deallocatePixelMap();
	test.deallocatePixelMap();
	reference.closeFile();
	test.closeFile();

	return 0;

}

