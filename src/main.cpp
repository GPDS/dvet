#include "../include/Image.h"
#include "../include/Video.h"
#include "../include/Sobel.h"
#include "../include/PSNR.h"
#include "../include/SSIM.h"
#include "../include/PWSSIM.h"
#include <streambuf>
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <fstream>

using namespace std;
#define row 2160
#define col 3840




int main (int argc, char const* argv[]){

	Video reference,test;

	PSNR  psnr;
	SSIM ssim;
	PWSSIM pwssim;

	// set input pareameters
	
	
	reference.setCoefs(2,2,row,col);
	reference.openFile(argv[1],row,col);
	test.setCoefs(2,2,row,col);
	string entrada = "";
	
	test.openFile(argv[2],row,col);
	


	
	int numFrames = test.returnFrames();
	cout << "Colunas: " << col << " Linhas: " << row << " Frames: " << numFrames << endl;


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

