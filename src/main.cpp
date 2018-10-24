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
#include <stdlib.h>
#include <cstring>
#include <sstream> 
#include <fstream>
#include <vector> 

using namespace std;

void usage(){
	cout << "Use the command (Exemple): \n"
			"./bin/main -ref [reference video] -eva [evaluated video] -wht [frames width] -htg [frames height] -f [number of frames]\n" 
			"Example:\n"
			"./bin/main video_reference.yuv video_test.yuv -wht 3840 -hgt 2160 -f 120"<< endl;
}


int converterStrToInt(string str){
    stringstream convert(str); 
    int temp_nuber;
    if(!(convert >> temp_nuber))
        return 0;
    return temp_nuber;
}


int main (int argc, char const* argv[]){
	if (argc < 4){
		usage();
		return 0;
	}

	//create variables and set the defalt parameters values
	int numFrames 	= 130,
		row 		= 2160,	
		col 		= 3840; 

	string ref_path = "", eva_path = "";

	Video reference,test;
	PSNR  psnr;
	SSIM ssim;
	PWSSIM pwssim;

	// set input pareameters
	vector<string> command_input;
    for (int i = 0; i < argc; i++){
        command_input.push_back(argv[i]);
    }


	for (int i = 0; i < argc; i++){
		if (command_input[i].compare("-f") == 0){
			numFrames = converterStrToInt(command_input[i+1]);
		}else if (command_input[i].compare("-wht") == 0){
			row = converterStrToInt(command_input[i+1]);
		}else if (command_input[i].compare("-hgt") == 0){
			col = converterStrToInt(command_input[i+1]);
		}else if (command_input[i].compare("-eva") == 0){
			eva_path = command_input[i+1];
		}else if (command_input[i].compare("-ref") == 0){
			ref_path =  command_input[i+1];
		}
	}


	reference.setCoefs(2,2,row,col);
	reference.openFile(ref_path.c_str(),row,col);
	test.setCoefs(2,2,row,col);
	string entrada = "";
	test.openFile(eva_path.c_str(),row,col);

	
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

