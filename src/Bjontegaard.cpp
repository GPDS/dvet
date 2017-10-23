#include "../include/Bjontegaard.h"

using namespace std;

#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)>(b)?(a):(b))


Bjontegaard::Bjontegaard( vector<double> psnr_e, vector<double> rate_e, vector<double> psnr_r, vector<double> rate_r){
    this->countOfElements = psnr_e.size();
    initBD();
    std::copy(psnr_e.begin(), psnr_e.end(), this->psnr_eva);
    std::copy(rate_e.begin(), rate_e.end(), this->rate_eva);
    std::copy(psnr_r.begin(), psnr_r.end(), this->psnr_ref);
    std::copy(rate_r.begin(), rate_r.end(), this->rate_ref);
	this->order = 3; //defalt order value
    // for (int i = 0; i < countOfElements; ++i)
    // {
    //     cout << " XX===> " << psnr_eva[i] << " ===> " << rate_eva[i]<< " ===> " << psnr_ref[i] << " ===> " << rate_ref[i]   << endl;
    // }
}

void Bjontegaard::initBD() {
    this->psnr_eva = (double*) malloc(sizeof(double) * this->countOfElements);
    this->rate_eva = (double*) malloc(sizeof(double) * this->countOfElements);
    this->psnr_ref = (double*) malloc(sizeof(double) * this->countOfElements);
    this->rate_ref = (double*) malloc(sizeof(double) * this->countOfElements);
}


int Bjontegaard::polyfit(double* input_a, double* input_b, double* coefficients){
    enum {maxOrder = 5};
    double B[maxOrder+1] = {0.0f};
    double P[((maxOrder+1) * 2)+1] = {0.0f};
    double A[(maxOrder + 1)*2*(maxOrder + 1)] = {0.0f};
    double x, y, powx;

    if (countOfElements <= order)
        return -1;

    if (order > maxOrder)
        return -1;

    for (int i = 0; i < countOfElements; i++) {
        x    = input_a[i];
        y    = input_b[i];
        powx = 1;

        for (int j = 0; j < (order + 1); j++) {
            B[j] = B[j] + (y * powx);
            powx  = powx * x;
        }
    }

    P[0] = countOfElements;

    for (int i = 0; i < countOfElements; i++) {
        x    = input_a[i];
        powx = input_a[i];

        for (int j = 1; j < ((2 * (order + 1)) + 1); j++) {
            P[j] = P[j] + powx;
            powx  = powx * x;
        }
    }

    for (int i = 0; i < (order + 1); i++) {
        for (int j = 0; j < (order + 1); j++) {
            A[(i * (2 * (order + 1))) + j] = P[i+j];
        }
        A[(i*(2 * (order + 1))) + (i + (order + 1))] = 1;
    }

    for (int i = 0; i < (order + 1); i++) {
        x = A[(i * (2 * (order + 1))) + i];
        if (x != 0){
            for (int k = 0; k < (2 * (order + 1)); k++){
                A[(i * (2 * (order + 1))) + k] = 
                    A[(i * (2 * (order + 1))) + k] / x;
            }

            for (int j = 0; j < (order + 1); j++) {
                if ((j - i) != 0) {
                    y = A[(j * (2 * (order + 1))) + i];
                    for (int k = 0; k < (2 * (order + 1)); k++) {
                        A[(j * (2 * (order + 1))) + k] = 
                            A[(j * (2 * (order + 1))) + k] -
                            y * A[(i * (2 * (order + 1))) + k];
                    }
                }
            }
        } else {
            return -1;
        }
    }

    for (int i = 0; i < (order + 1); i++) {
        for (int j = 0; j < (order + 1); j++) {
            x = 0;
            for (int k = 0; k < (order + 1); k++) {
                x = x + (A[(i * (2 * (order + 1))) + (k + (order + 1))] * B[k]);
            }
            coefficients[i] = x;
        }
    }
    return 0;
}

double find_min(double *vet,int vet_size) {
	double min;
	min = vet[0];
	for (int i=1; i<vet_size; i++) {
		min = MIN(min, vet[i]);
	}
	return min;
}

double find_max(double *vet,int vet_size) {
	double max;
	max = vet[0];
	for (int i=1; i<vet_size; i++) {
		max = MAX(max, vet[i]);
	}
	return max;
}

void Bjontegaard::polyint(double *c_in, int deg, double *vet_out) {
	vet_out[0] = 0;
	for (int i=1; i<deg+2; i++) {
		vet_out[i] = c_in[i-1]/i;
	}
}

double Bjontegaard::polyval(double *c_in, int deg, double  x_in) {
	double x;
	double result;
	x=1;
	result=0;
	for (int i=0;i<deg+1;i++) {
		result+=c_in[i]*x;
		x*= x_in;
	}
	return result;
}

double Bjontegaard::BD_rate(){

    int 	deg = 3;

	double 	max = 0, min = 0, 
			int1 = 0, int2 = 0,
			rate = 0;

	double  *p1i, *p2i,
			*coefficients1, *coefficients2,
			*rate1, *rate2;

	p1i = (double *)malloc(sizeof(*p1i)*(deg+2));
	p2i = (double *)malloc(sizeof(*p2i)*(deg+2));
	
	coefficients1 = (double *)malloc(sizeof(*coefficients1)*(deg+1));
	coefficients2 = (double *)malloc(sizeof(*coefficients2)*(deg+1));

	rate1 = (double *)malloc(sizeof(*rate1)*countOfElements);
	rate2 = (double *)malloc(sizeof(*rate2)*countOfElements);

	//computer log
	for (int i = 0; i < countOfElements; i++) {
    	rate1[i] = log(((double)rate_ref[i]));
  	}
  	for (int i = 0; i < countOfElements; i++) {
    	rate2[i] = log(((double)rate_eva[i]));
  	}
	//computer polyfit
	polyfit(psnr_ref, rate1, coefficients1);
	polyfit(psnr_eva, rate2, coefficients2);

	//find max and min
	max = MIN(find_max(psnr_ref, countOfElements), find_max(psnr_eva, countOfElements));
	min = MAX(find_min(psnr_ref, countOfElements), find_min(psnr_eva, countOfElements));

	polyint(coefficients1, deg, p1i);
	polyint(coefficients2, deg, p2i);

	int1=polyval(p1i,deg+1,max)-polyval(p1i,deg+1,min);
  	int2=polyval(p2i,deg+1,max)-polyval(p2i,deg+1,min);

  	rate = (int2-int1)/(max-min);
  	rate=(exp(rate)-1)*100;

  	cout <<	"BD_Rate:  " << rate << endl;
  	/*conserto relatado no BDPSNR.h*/
  		
	return rate;
}

double Bjontegaard::BD_avg(){

    int 	deg = 3;
	double 	max = 0, min = 0, 
			int1 = 0, int2 = 0,
			avg = 0;

	double  *p1i, *p2i,
			*coefficients1, *coefficients2,
			*rate1, *rate2;

	p1i = (double *)malloc(sizeof(*p1i)*(deg+2));
	p2i = (double *)malloc(sizeof(*p2i)*(deg+2));
	
	coefficients1 = (double *)malloc(sizeof(*coefficients1)*(deg+1));
	coefficients2 = (double *)malloc(sizeof(*coefficients2)*(deg+1));

	rate1 = (double *)malloc(sizeof(*rate1)*countOfElements);
	rate2 = (double *)malloc(sizeof(*rate2)*countOfElements);

	//computer log
	for (int i = 0; i < countOfElements; i++) {
    	rate1[i] = log(((double)rate_ref[i]));
  	}
  	for (int i = 0; i < countOfElements; i++) {
    	rate2[i] = log(((double)rate_eva[i]));
  	}
  	//cout << psnr_ref[0] << " " << rate_ref[0] << " - 2 -" << psnr_eva[0] << " " << rate_eva[0] << endl;

	//computer polyfit
	polyfit(rate1, psnr_ref, coefficients1);
	polyfit(rate2, psnr_eva, coefficients2);

	//find max and min
	max = MIN(find_max(rate1, countOfElements), find_max(rate2, countOfElements));
	min = MAX(find_min(rate1, countOfElements), find_min(rate2, countOfElements));

	polyint(coefficients1, deg, p1i);
	polyint(coefficients2, deg, p2i);

	int1=polyval(p1i,deg+1,max)-polyval(p1i,deg+1,min);
  	int2=polyval(p2i,deg+1,max)-polyval(p2i,deg+1,min);

  	avg = (int2-int1)/(max-min);

  	cout <<	"BD_PSNR:  " << avg << endl;
	
	return avg;
}

