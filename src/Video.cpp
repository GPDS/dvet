#include "common.h"
#include "Image.h"
#include "Video.h"

	void Video::setNumberOfFrames(int row, int col)
	{
		file.seekg(0, file.end);
		long sizeBytes = file.tellg();	
		numberOfFrames = sizeBytes /(row*col*coef_mult);
	}

	void Video::setCoefs (int coef1 , int coef2,int row, int col)
	{
		//d1 and d2 are private's variables 
		this->d1 = coef1;
		this->d2 = coef2;
			
		this->coef_mult = (1+((float)1/(d1*d1)) + ((float)1/(d2*d2)));

		/*Coefs_mult is a variable
		This is table:
			For a 444 Video set d1=1, d2= 1 and coef_mult = 3
			For a 442 Video set d1=1, d2=2 and coef_mult = 2
			For a 440 Video set d1=2 d2=2 and coef_mult = 1.5
			Example:
			if d1 = 2 and d2=2 =  coef_mult = 1.5	
		*/
		
		//Use the class Image to set this values
		//frame is the object of class Image
		frame.setRow(row);
		frame.setCol(col);
		frame.setCoefs(this->d1 , this->d2);	
		
		frame.allocatePixelMap_Y();
		frame.allocatePixelMap_Cb();
		frame.allocatePixelMap_Cr();
	}

	void Video::openFile(const char* Name, int row , int col)
	{
		file.open (Name, ios::in | ios::binary);
		if (!file.is_open())
			cout << "File isn't open!" << endl;

		setNumberOfFrames(row , col);
	}

	void Video::closeFile()
	{
		file.close();	
	}

	void Video::readVideo(int frameNumber,int row , int col)
	{	
			long pos, size;
			size = row*col*coef_mult;
			
			pos = size*frameNumber;
			file.seekg(pos,ios::beg);
			frame.setPixelMap_Y(file);
			frame.setPixelMap_Cb(file);		
			frame.setPixelMap_Cr(file);

			

	}
	
	//This member function write in file the frames
	void Video::writeVideo(int frameNumber,int row , int col)
	{	fstream Name;
		if(frameNumber==0)
			Name.open("Video.yuv",  ios::binary|ios::out);
		
		else
			 Name.open("Video.yuv", ios::app | ios::binary|ios::out);

		if (!Name)
			cout << "File isn't open!!" << endl;
			
		else //if the file is open
		{
			frame.writePixelMap_Y(Name);
			frame.writePixelMap_Cb(Name);
			frame.writePixelMap_Cr(Name);
		}
		Name.close();

	}
	void Video::deallocatePixelMap(){
		frame.deallocatePixelMap_Y();
		frame.deallocatePixelMap_Cb();
		frame.deallocatePixelMap_Cr();
	
	}
	//This member function return the Number of the frames
	int Video::returnFrames()
	{
		return this->numberOfFrames;
	}
	Image Video::getFrame(){
		return frame;
	}

	char Video::getPtrstream_Y(int row, int col){

		return	frame.getPixel_Y(row,col);
	}
	
	void Video::getCoefs(int coefs[])
	{
		coefs[0] = this->d1;
		coefs[1] = this-> d2;
	}
