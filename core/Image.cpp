#include "Image.h"

Image::Image()
{
	
}

void Image::setCoefs(float coefs[]){
	d1 = (int)coefs[0];
	d2 = (int)coefs[1];
	coef_mult = coefs[2];
}

void Image::setCol(int X)
{
    if (X > 0) Col = X;
}


void Image::setRow(int Y)
{
    if (Y > 0) Row = Y;
}

int Image::getCol()
{
	return Col;
}


int Image::getRow()
{
	return Row;
}

unsigned long Image::getNumberOfPixels()
{
    return Col*Row;
}

void Image::allocate_PixelMap_Y()
{
    PixelMap_Y=new unsigned char*[Col];
	for(int i=0;i<Col;i++)
		PixelMap_Y[i]= new unsigned char[Row];
}

void Image::deallocate_PixelMap_Y(){
		for(int i=0;i<Col;i++)
			delete [] PixelMap_Y[i];

		delete [] PixelMap_Y;
}

void Image::allocate_PixelMap_Cb()
{
    PixelMap_Cb=new unsigned char*[Col/d1];
    for(int i=0;i<Col/d1;i++)
    	PixelMap_Cb[i] = new unsigned char[Row/d2];
}

void Image::allocate_PixelMap_Cr()
{
	PixelMap_Cr=new unsigned char*[Col/d1];
	for(int i=0;i<Col/d1;i++)
    	PixelMap_Cr[i] = new unsigned char[Row/d2];
}

void Image::deallocate_PixelMap_Cb()
{
	for(int i=0;i<Col/d1;i++)
		delete [] PixelMap_Cb[i];
		
	delete [] PixelMap_Cb;
}

void Image::deallocate_PixelMap_Cr()
{
	for(int i=0;i<Col/d2;i++)
		delete [] PixelMap_Cr[i];
	
	delete [] PixelMap_Cr;
}

void Image::set_PixelMap_Y(FILE *in)
{
	for(int i=0;i<Col;i++)
		fread(PixelMap_Y[i],1,Row,in);
}
void Image::set_PixelMap_Cb(FILE *in)
{
	for(int i=0;i<Col/d1;i++)
		fread(PixelMap_Cb[i],1,Row/d2,in);
}
 
 void Image::set_PixelMap_Cr(FILE *in)
 {
	for(int i=0;i<Col/d1;i++)
		fread(PixelMap_Cr[i],1,Row/d2,in);
 }

void Image::print_PixelMap_Y(FILE *out){


		for(int i=0;i<Col;i++){
		fwrite(PixelMap_Y[i],1,Row,out);

	}

}

void Image::print_PixelMap_Cb(FILE *out){



  for(int i=0;i<Col/d1;i++){
		fwrite(PixelMap_Cb[i],1,Row/d2,out);

	}




}

void Image::print_PixelMap_Cr(FILE *out){


		for(int i=0;i<Col/d1;i++){
		fwrite(PixelMap_Cr[i],1,Row/d2,out);

	}



}


int Image::get_Y_PixelMap(int row, int col){


	return PixelMap_Y[col][row];

}
int Image::get_Cb_PixelMap(int row, int col){


	return PixelMap_Cb[col][row];

}

int Image::get_Cr_PixelMap(int row, int col){


	return PixelMap_Cr[col][row];

}



int Image::set_Y(int row, int col,char value){


	 	PixelMap_Y[col][row]=value;

}
int Image::set_Cb(int row, int col,char value){


	 	PixelMap_Cb[col][row]=value;

}

int Image::set_Cr(int row, int col,char value){


	 	PixelMap_Cr[col][row]=value;

}

void Image::zero_Cb(){

	for(int i=0;i<Col/d1;i++){
		for(int j=0;j<Row/d2;j++){
			PixelMap_Cb[i][j]=128;
		}

	}
}

void Image::zero_Cr(){

	for(int i=0;i<Col/d1;i++){
		for(int j=0;j<Row/d2;j++){
			PixelMap_Cr[i][j]=128;
		}

	}
}

