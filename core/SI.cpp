#include "SI.h"

void SI::ComputeSI(Video refvideo,Sobel refsobel ,int row ,int col){
	
	int i,j,k;
	int NoFrames;
	NoFrames = refvideo.returnFrames();
	double *si_tmp = new double[row*col];
	double avg=0,std=0;
	Image ref;
	float coefs[3];
	
	refvideo.getCoefs(coefs);
	refsobel.allocate_Pixelmaps(row,col,coefs);

	for(i=0;i<NoFrames;i++){
		refvideo.readVideo(i,row,col);
		ref = refvideo.getFrame(i);
		refsobel.Sobel_Operation(ref);
		for(j=0;j<row;j++){
			for(k=0;k<col;k++){
				avg += refsobel.get_Sobel_Ptrstream(j,k);

			}		
		
		}
		
		avg /= (row*col);

		for(j=0;j<row;j++){
			for(k=0;k<col;k++){
				std += pow( refsobel.get_Sobel_Ptrstream(j,k) - avg,2 );

			}		
		
		}

		std = sqrt(std/(row*col-1));

		si_tmp[i] = std;
		avg = 0;
		std = 0;
	}
	SI_avg = si_tmp[0];

	for(i=1;i<NoFrames;i++){
		
		if(SI_avg<si_tmp[i])
			SI_avg = si_tmp[i];

	}
	refsobel.deallocate_Pixelmaps();
}

double SI::get_SI(){
	return SI_avg;
}

void SI::writeSI(){
	
	FILE *SI;
	SI = fopen("SI.txt","a+");
	if(!SI){
		cout << "Erro ao abrir o arquivo" << endl;	
	}
	fprintf(SI,"%lf\n",SI_avg);
	fclose(SI);
	
	
	
}
