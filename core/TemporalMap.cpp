#include "TemporalMap.h"

void TemporalMap::allocate_Pixelmaps(int row , int col,float coefs[]){

	temporalMap.setCol(col);
	temporalMap.setRow(row);
	temporalMap.setCoefs(coefs);
	temporalMap.allocate_PixelMap_Y();
	temporalMap.allocate_PixelMap_Cb();
	temporalMap.allocate_PixelMap_Cr();

}

void TemporalMap::deallocate_Pixelmaps(){

	temporalMap.deallocate_PixelMap_Y();
	temporalMap.deallocate_PixelMap_Cb();
	temporalMap.deallocate_PixelMap_Cr();

}
void TemporalMap::generateTemporalMap(Image Sample1,Image Sample2){

	unsigned char temp;
	int row, col;

	row = Sample1.getRow();
	col = Sample1.getCol();

	for (int i=0;i<row;i++){
		for(int j=0;j<col;j++){

			temp = (char) sqrt( pow( Sample1.get_Y_PixelMap(i,j) - Sample2.get_Y_PixelMap(i,j),2  ) ) ;
			temporalMap.set_Y(i,j,temp);


		}

	}

}

void TemporalMap::writeFrames(int frame,int row, int col){

	FILE *out;
	if(frame==0)
		out = fopen("TemporalMap.yuv","wb");
	else
		out = fopen("TemporalMap.yuv","r+b");
		long pos,size;
	size=row*col*1.5;
	pos = size *frame;
	fseek(out,pos,SEEK_SET);
	temporalMap.print_PixelMap_Y(out);
	temporalMap.zero_Cb();
	temporalMap.zero_Cr();
	temporalMap.print_PixelMap_Cb(out);
	temporalMap.print_PixelMap_Cr(out);
	fclose(out);

}

int TemporalMap::get_TemporalMap_Ptrstream(int row, int col){

	return temporalMap.get_Y_PixelMap(row,col);

}
