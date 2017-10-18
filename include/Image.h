#include <fstream>

#ifndef Image_h
#define Image_h


using namespace std;

class Image
{
	public:
		
		void setRow (int row);
		void setCol (int col);
		void setCoefs (int coef1 , int coef2);	
		int getRow ();
		int getCol ();
		unsigned long int getNumberOfPixels ();
		

		void allocatePixelMap_Y ();
		void allocatePixelMap_Cb ();
		void allocatePixelMap_Cr ();

		void deallocatePixelMap_Y();
		void deallocatePixelMap_Cb();
		void deallocatePixelMap_Cr();
		
		void writePixelMap_Y(fstream &out);
		void writePixelMap_Cb(fstream &out);
		void writePixelMap_Cr(fstream &out);

		void setPixelMap_Y (fstream &in);
		void setPixelMap_Cb (fstream &in);
		void setPixelMap_Cr (fstream &in);	
		
		void setPixel_Y(int x , int y , char value);
		void setPixel_Cb(int x , int y , char value);
		void setPixel_Cr(int x , int y , char value);		
		
		char getPixel_Y(int x , int y);
		char getPixel_Cb(int x , int y);
		char getPixel_Cr(int x , int y);

		double getSumY ();
		double getSumCb ();
		double getSumCr ();
		double getMediaY();
		double getMediaCb();
		double getMediaCr();

		void zero_Cb();
    	void zero_Cr();

	private:
		int row;
		int col;
		char **PixelMap_Y;
		char **PixelMap_Cb;
		char **PixelMap_Cr; 
		int d1, d2;//dimensions of Cb and Cr
		float coef_mult; //size of frame (Y+Cb+Cr)
		
};

#endif

