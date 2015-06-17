#include "Video.h"


Video::Video(){
		
		//For a 444 Video set d1=1, d2= 1 and coef_mult = 3
		//For a 442 Video set d1=1, d2=2 and coef_mult = 2
		// For a 440 Video set d1=2 d2=2 and coef_mult = 1.5
	//	coef_mult = 1.5;	
	//	d1 = 2;
	//	d2=2;	


}

void Video::setCoefs(float coefs[]){
	
	d1 = (int)coefs[0];
	d2 = (int)coefs[1];
	coef_mult = coefs[2];

}

void Video::getCoefs(float coefs[])
{
	coefs[0] = d1;
	coefs[1]= d2;
	coefs[2] = coef_mult;
	
}

void Video::setNumberOfFrames(int row, int col){
    int NumberPixels=col*row;
    long V_tmpSize = 0;

    fseek(V_fileStream, 0, SEEK_END);

    V_tmpSize = ftell(V_fileStream);

    Sizebytes = V_tmpSize;
    NumberOfFrames = Sizebytes/( NumberPixels*coef_mult);
  
}

void Video::AllocFrame(){
    Frame= new Image[NumberOfFrames];

}

void Video::OpenFile(const char name[],int row, int col){
			
    V_fileStream=fopen(name,"rb");
    if(!V_fileStream){
        cout << "Erro ao abrir o arquivo aqui" << endl;

    }
   setNumberOfFrames(row,col);
  AllocFrame();
   
    
}
void Video::DeallocFrame(){
	
	delete [] Frame;


}

int Video::get_Y_Ptrstream(int frame,int row, int col){

	return Frame[frame].get_Y_PixelMap(row,col);
}

int Video::returnFrames(){
	return NumberOfFrames;
}

void Video::readVideo(int frame,int row, int col){
	
		
		long pos,size;
		float coefs[]={d1,d2,coef_mult};

		size = row*col*coef_mult;

		Frame[frame].setRow(row);
		Frame[frame].setCol(col);	
		Frame[frame].setCoefs(coefs);
		Frame[frame].allocate_PixelMap_Y();
		Frame[frame].allocate_PixelMap_Cb();
		Frame[frame].allocate_PixelMap_Cr();
		pos = size *frame;
		fseek(V_fileStream,pos,SEEK_SET);
		Frame[frame].set_PixelMap_Y(V_fileStream);
		
		Frame[frame].set_PixelMap_Cb(V_fileStream);		
		Frame[frame].set_PixelMap_Cr(V_fileStream);
	
		
}

void Video::writeVideo(int frame,int row, int col){
	FILE *out;
	if(frame==0)
		out = fopen("Video.yuv","wb");
	else
		out = fopen("Video.yuv","r+b");
	if(!out){
		cout <<	"Erro ao abrir o video" << endl;
		exit(-1);
	}
	float coefs[]={d1,d2,coef_mult};
		Frame[frame].setCoefs(coefs);
	long pos,size;
	size=row*col*coef_mult;
	pos = size *frame;
	fseek(out,pos,SEEK_SET);
	Frame[frame].print_PixelMap_Y(out);
	Frame[frame].print_PixelMap_Cb(out);
	Frame[frame].print_PixelMap_Cr(out);
	fclose(out);

}
Image Video::getFrame(int frame){
	
	return Frame[frame];

}


