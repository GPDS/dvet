#ifndef VIDEO_H
#define VIDEO_H

#include "Image.h"

using namespace std;

class Video{

public:
		Video();
     void setNumberOfFrames(int row, int col);
     void setCoefs(float coefs[]);
     void getCoefs(float coefs[]);
     void AllocFrame();
     void DeallocFrame();
     void OpenFile(const char name[],int row, int col);
     int returnFrames();
     void readVideo(int frame,int row, int col);
    int get_Y_Ptrstream(int frame,int row, int col);
    void writeVideo(int frame,int row, int col);
    Image getFrame(int frame);
     
private:
    Image *Frame;
    long Sizebytes;
    int NumberOfFrames;
    FILE *V_fileStream;
    int d1,d2;
    float coef_mult;
};

#endif // VIDEO_H
