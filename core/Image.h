
#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <time.h>
using namespace std;

class Image {

public:
    Image();
    int getRow ();
    int getCol ();
    void setCoefs(float coefs[]);
    unsigned long getNumberOfPixels ();
    void setRow( int Row);
    void setCol( int Col);
    void allocate_PixelMap_Y();
    void allocate_PixelMap_Cb();
    void allocate_PixelMap_Cr();
    void deallocate_PixelMap_Y();
    void deallocate_PixelMap_Cb();
    void deallocate_PixelMap_Cr();
    void set_PixelMap_Y(FILE *in);
    void set_PixelMap_Cb(FILE *in);
    void set_PixelMap_Cr(FILE *in);
    void print_PixelMap_Y(FILE *out);
    void print_PixelMap_Cb(FILE *out);
    void print_PixelMap_Cr(FILE *out);
    int  get_Y_PixelMap(int row, int col);
    int  get_Cb_PixelMap(int row, int col);
     int  get_Cr_PixelMap(int row, int col);
    int  set_Y(int row, int col,char value);
    int  set_Cb(int row, int col,char value);
    int  set_Cr(int row, int col,char value);

    void zero_Cb();
    void zero_Cr();

private:
    int Row;
    int Col;
    int d1,d2;
    float coef_mult;
    unsigned char **PixelMap_Y;
    unsigned char **PixelMap_Cb;
    unsigned char **PixelMap_Cr;
};



#endif // IMAGE_H
