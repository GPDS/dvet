#include "main.h"

void Sobel::allocatePixelMap(int row, int col,int coef1, int coef2){

	sobel.setCol(col);
	sobel.setRow(row);
	sobel.setCoefs(coef1 ,coef2);
	sobel.allocatePixelMap_Y();
	sobel.allocatePixelMap_Cb();
	sobel.allocatePixelMap_Cr();
}

void Sobel::writeFrames(int frameNumber, int row , int col){
	printf("entrou sobel\n");
	fstream Name;
	if(frameNumber==0)
		Name.open("Sobel.yuv",  ios::binary|ios::out);
		
	else
		Name.open("Sobel.yuv", ios::app | ios::binary|ios::out);

	if(!Name)
		cout << "The file couldn't open" << endl;

	else{
		
		sobel.writePixelMap_Y(Name);
		sobel.zero_Cb();
    	sobel.zero_Cr();
		sobel.writePixelMap_Cb(Name);
		sobel.writePixelMap_Cr(Name);
		Name.close();
	}
}

void Sobel::deallocatePixelMap(){

	sobel.deallocatePixelMap_Y();
	sobel.deallocatePixelMap_Cb();
	sobel.deallocatePixelMap_Cr();

}

int Sobel::get_Sobel_Ptrstream(int row, int col){
	return sobel.getPixel_Y(row,col);
}


void Sobel::Sobel_Operation (Image in)
{
 	int width,height;

 	width = in.getRow();
 	height = in.getCol();
 	//i for Number of Col and j for Number of Row
    int i=0,j=0;

   //Gradient of image in horizontal and vertical direction and final gradient



   //Applying sobel operator; for each frame; only Y Plane
     for (i = 1; i < height-1; i++)//Number of Cols
     {
     	for (j = 1; j < width-1; j++) //Number of rows
        {
			float Gradient_x=0, Gradient_y =0;
   			unsigned char Pixel_Value = 0 ;
            Gradient_x +=  -in.getPixel_Y(i-1,j-1) -2*in.getPixel_Y(i-1,j) - in.getPixel_Y(i-1,j+1);
            Gradient_x +=  in.getPixel_Y(i+1,j-1) +2*in.getPixel_Y(i+1,j) + in.getPixel_Y(i+1,j+1);
                    
			Gradient_y +=  -in.getPixel_Y(i-1,j-1) + in.getPixel_Y(i-1,j+1);
            Gradient_y +=  -2*in.getPixel_Y(i,j-1) + 2*in.getPixel_Y(i,j+1);
            Gradient_y +=  -1* in.getPixel_Y(i+1,j-1) + in.getPixel_Y(i+1,j+1);
            //Assign to image
           Pixel_Value = (char) sqrt (Gradient_x * Gradient_x + Gradient_y * Gradient_y);  
    	    Pixel_Value %=255; 
			sobel.setPixel_Y(i,j,Pixel_Value);
			
         }
			
     }

}
