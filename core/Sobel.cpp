#include "Sobel.h"



void Sobel::allocate_Pixelmaps(int row, int col,float coefs[]){

	sobel.setCol(col);
	sobel.setRow(row);
	sobel.setCoefs(coefs);
	sobel.allocate_PixelMap_Y();
	sobel.allocate_PixelMap_Cb();
	sobel.allocate_PixelMap_Cr();


}



void Sobel::writeFrames(int frame, int row , int col){

	FILE *out;
	if(frame==0)
		out = fopen("sobel.yuv","wb");
	else
		out = fopen("sobel.yuv","r+b");
		long pos,size;
	size=row*col*1.5;
	pos = size *frame;
	fseek(out,pos,SEEK_SET);
	sobel.print_PixelMap_Y(out);
	sobel.zero_Cb();
    sobel.zero_Cr();
	sobel.print_PixelMap_Cb(out);
	sobel.print_PixelMap_Cr(out);
	fclose(out);




}
void Sobel::Sobel_Operation ( Image teste  )
{
 			int Width,Height;

 			Width = teste.getRow();
 			Height = teste.getCol();

 			   //i for Number of Col and j for Number of Row
    int i=0,j=0;

   //Gradient of image in horizontal and vertical direction and final gradient
    float Gradient_x=0, Gradient_y =0;
      char Pixel_Value = 0 ;






      //Applying sobel operator; for each frame; only Y Plane
        for (i = 1; i < Height-1; i++)//Number of Cols
            {
                  for (j = 1; j < Width-1; j++) //Number of rows
                  {
                    Gradient_x =0;
                    Gradient_y =0;
                    Gradient_x +=  -teste.get_Y_PixelMap(j-1,i-1) -2*teste.get_Y_PixelMap(j,i-1) - teste.get_Y_PixelMap(j+1,i-1);
                    Gradient_x +=  teste.get_Y_PixelMap(j-1,i+1) +2*teste.get_Y_PixelMap(j,i+1) + teste.get_Y_PixelMap(j,i+1);
                    Gradient_y +=  -teste.get_Y_PixelMap(j-1,i-1) + teste.get_Y_PixelMap(j+1,i-1);
                    Gradient_y +=  -2*teste.get_Y_PixelMap(j-1,i) + 2*teste.get_Y_PixelMap(j+1,i);
                    Gradient_y +=  -1* teste.get_Y_PixelMap(j-1,i+1) + teste.get_Y_PixelMap(j,i+1);
                    //Assign to image
                    Pixel_Value = ( char ) sqrt ( Gradient_x * Gradient_x + Gradient_y * Gradient_y ) ;
                    //if(Pixel_Value>255)
                      //  Pixel_Value = 255;
                    sobel.set_Y(j,i,Pixel_Value);

                  }

            }






}

int Sobel::get_Sobel_Ptrstream(int row, int col){

	return sobel.get_Y_PixelMap(row,col);

}
void Sobel::deallocate_Pixelmaps(){

	sobel.deallocate_PixelMap_Y();
	sobel.deallocate_PixelMap_Cb();
	sobel.deallocate_PixelMap_Cr();

}

