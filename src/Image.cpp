#include "main.h"

	void Image::setRow (int row)
	{
		this->row=row;
	}
	
	void Image::setCol (int col)
	{
		this->col=col;
	}
	
	int Image::getRow ()
	{
		return row;
	}
	
	int Image::getCol ()
	{
		return col;
	}

	void Image::setCoefs (int coef1 , int coef2)
	{
		this->d1 = coef1;
		this->d2 = coef2;
		//d1 and d2 are private's variables 
		this->coef_mult = (1+((float)1/(d1*d1)) + ((float)1/(d2*d2)));
	}		

	unsigned long int Image::getNumberOfPixels ()
	{
		return (row*col);
	}

	void Image::allocatePixelMap_Y ()
	{
		this->PixelMap_Y = new char *[col];

		for (int i=0 ; i<col ; i++)
			this->PixelMap_Y[i] = new  char [row];
		
	}

	void Image::allocatePixelMap_Cb ()
	{
		this->PixelMap_Cb = new  char *[col/d1];

		for (int i=0 ; i<col/d1 ; i++)
			this->PixelMap_Cb[i] = new  char [row/d1];
		

	}
	void Image::allocatePixelMap_Cr ()
	{
		this->PixelMap_Cr = new  char *[col/d2];

		for (int i=0 ; i<col/d1 ; i++)
			this->PixelMap_Cr[i] = new  char [row/d2];
			
	}

	void Image::deallocatePixelMap_Y()
	{
		for (int i=0 ; i<col ; i++)
			delete [] PixelMap_Y[i];

		delete [] PixelMap_Y;
	}


	void Image::deallocatePixelMap_Cb()
	{
		for (int i=0 ; i<col/d1 ; i++)
			delete [] PixelMap_Cb[i];

		delete [] PixelMap_Cb;

	}
	void Image::deallocatePixelMap_Cr()
	{
		for (int i=0 ; i<col/d2 ; i++)
			delete [] PixelMap_Cr[i];

		delete [] PixelMap_Cr;
	}
	

	
	void Image::writePixelMap_Y(fstream &out)
	{
		for(int i =0;i<col;i++)
			out.write(PixelMap_Y[i],row);
	}
	void Image::writePixelMap_Cb(fstream &out)
	{
		for(int i =0;i<col/d1;i++)
			out.write(PixelMap_Cb[i],row/d1);
	}
	void Image::writePixelMap_Cr(fstream &out)
	{
		for(int i =0;i<col/d2;i++)
			out.write(PixelMap_Cr[i],row/d2);
	}



	void Image::setPixelMap_Y (fstream &in)
	{
		for(int i =0;i<col;i++)
			in.read(PixelMap_Y[i],row);
	}
	void Image::setPixelMap_Cb (fstream &in)
	{
		for(int i =0;i<col/d1;i++)
			in.read(PixelMap_Cb[i],row/d1);
	}
	void Image::setPixelMap_Cr (fstream &in)
	{
		for(int i =0;i<col/d2;i++)
			in.read(PixelMap_Cr[i],row/d2);
	}	


		
	void Image::setPixel_Y(int x , int y , char value)
	{
		PixelMap_Y[x][y] = value;
	}
	void Image::setPixel_Cb(int x , int y , char value)
	{
		PixelMap_Cb[x][y]=value;
	}
	void Image::setPixel_Cr(int x , int y , char value)
	{
		PixelMap_Cr[x][y]=value;
	}	


	char Image::getPixel_Y(int x , int y)
	{
		return PixelMap_Y[x][y];
	}
	char Image::getPixel_Cb(int x , int y)
	{
		return PixelMap_Cb[x][y];
	}
	char Image::getPixel_Cr(int x , int y)
	{
		return PixelMap_Cr[x][y];
	}
		

	//The next funccion return the sum of all Y's pixels
	double Image::getSumY ()
	{
		double sum=0;
		for (register int i=0 ; i<col ; i++)
		{
			for(register int j=0 ; j<row ; j++)
			{
				sum += PixelMap_Y[i][j];
			}
		}
		return sum;	
	}	

	//The next funccion return the sum of all Cb's pixels
	double Image::getSumCb ()
	{
		double sum=0;
		for (register int i=0 ; i<col/d1 ; i++)
		{
			for(register int j=0 ; j<row/d1 ; j++)
			{
				sum += PixelMap_Cb[i][j];
			}
		}
		return sum;	
	}

	//The next funccion return the sum of all Cr's pixels
	double Image::getSumCr ()
	{
		double sum=0;
		for (register int i=0 ; i<row/d2 ; i++)
		{
			for(register int j=0 ; j<col/d2 ; j++)
			{
				sum += PixelMap_Cr[i][j];
			}
		}
		return sum;	
	}


	double Image::getMediaY()
	{
		return (getSumY() / (row*col) );
	}

	double Image::getMediaCb()
	{
		return (getSumCb()*d1*d1 / (row*col) );
	
	}
	double Image::getMediaCr()
	{
		return (getSumCr()*d2*d2 / (row*col) );
	}


	void Image::zero_Cb()
	{
		for (int i = 0 ; i < col/d1 ; i++)
		{
			for	(int j=0 ; j< row/d1 ; j++)	
				PixelMap_Cb[i][j]=128;
		}
	}
   	void Image::zero_Cr()
	{
		for (int i = 0 ; i < col/d2 ; i++)
		{
			for	(int j=0 ; j< row/d2 ; j++)	
				PixelMap_Cr[i][j]=128;
		}
	}
