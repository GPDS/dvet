#include "TI.h"
#include "Video.h"

void TI::computeTI(Video tmpVideo, Video tmpVideo1, TemporalMap tmpTempMap,int row, int col)
{
	int i,j,k;
	int noframes = tmpVideo.returnFrames();
	double *ti_tmp = new double[noframes];
	double avg = 0, std = 0;
	Image tmp,tmp1;
	float coefs[3];

	tmpVideo.getCoefs(coefs);
	tmp.setCoefs(coefs);
	tmp1.setCoefs(coefs);
	tmpTempMap.allocate_Pixelmaps(row,col,coefs);
	for(i = 0; i < noframes - 1; i++)
	{

		tmpVideo.readVideo(i,row,col);
		tmpVideo1.readVideo(i+1,row,col);
		tmp = tmpVideo.getFrame(i);
		tmp1 = tmpVideo1.getFrame(i+1);
		tmpTempMap.generateTemporalMap(tmp,tmp1);
		tmpTempMap.writeFrames(i,row,col);

		for(j = 0; j < col; j++){
				for (k=0;k<row;k++){
					avg += tmpTempMap.get_TemporalMap_Ptrstream(j,k);

			}

		}

		avg /= (row*col);


			for(j = 0; j < col; j++){
				for (k = 0;k < row; k++){

					std += pow((tmpTempMap.get_TemporalMap_Ptrstream(j,k)- avg),2);

				}


		}



		std = sqrt(std/(row*col-1));


		ti_tmp[i] = std;

		avg = 0;
		std = 0;
	}


	TI_Avg = ti_tmp[0];

	for(i = 1; i < noframes - 1; i++)
	{

		if(TI_Avg < ti_tmp[i]){
				TI_Avg = ti_tmp[i];
		}
	}
	tmpTempMap.deallocate_Pixelmaps();
	cout << "TI = " << TI_Avg << endl;
}

double TI::getTI()
{
	return TI_Avg;
}

