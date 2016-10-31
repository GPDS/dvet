#ifndef Sobel_h
#define Sobel_h


class Sobel {
    public:
	void writeFrames(int frameNumber, int row, int col);
        void allocatePixelMap(int row, int col,int coef1, int coef2);
	void deallocatePixelMap();
        void Sobel_Operation ( Image teste);
	int get_Sobel_Ptrstream(int row,int col);

    private:
      
       Image sobel;
		//The object of the class Image

       
};

#endif
