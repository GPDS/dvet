#ifndef Video_h
#define Video_h

using namespace std;

class Video
{
	public:
	
	void setNumberOfFrames(int row, int col);
	void setCoefs (int coef1 , int coef2,int row, int col);
	void openFile(const char* Name, int row , int col);
	void closeFile();
	void readVideo(int frameNumber,int row , int col);
	void writeVideo(int frameNumber, int row , int col);
	int returnFrames();
	void deallocatePixelMap();
	
	void getCoefs(int coefs[]);
	char getPtrstream_Y(int row, int col);
	Image getFrame();
	
	private:
	Image frame;
	fstream file;
	int d1, d2;
	float coef_mult;
	int numberOfFrames;
};


#endif
