#include <string.h>
#include "image.hpp"
#include <iostream>
#include <fstream>

#define NSORTIES	8

#define LEARNING_LOOPS	50
#define LEARNING_ITERATION	500

#define QUERY_ITERATION	40

#define WEIGHT_DISPLAY_THREESHOLD	0.08

#define K 1.0
#define _ 0.0

#define NEXEMPLE	8
#define NENTREES	9

float lettre_C[NENTREES] ={ 	K,K,K,
								K,_,_,
								K,K,K};

float lettre_T[NENTREES] ={ 	K,K,K,
								_,K,_,
								_,K,_};

float lettre_U[NENTREES] ={ 	K,_,K,
								K,_,K,
								K,K,K};

float lettre_X[NENTREES] ={ 	K,_,K,
								_,K,_,
								K,_,K};

float lettre_L[NENTREES] ={ 	K,_,_,
								K,_,_,
								K,K,K};

float lettre_H[NENTREES] ={ 	K,_,K,
								K,K,K,
								K,_,K};

float lettre_D[NENTREES] ={ 	K,K,_,
								K,_,K,
								K,K,_};

float lettre_O[NENTREES] ={ 	_,K,_,
								K,_,K,
								_,K,_};

typedef float* Figure;

Figure* getPattern(int& ne,int &ni)
{
	ne = NEXEMPLE;
	ni = NENTREES;
	Figure* figure = new Figure[NEXEMPLE+1];
	figure[0] = lettre_C;
	figure[1] = lettre_T;
	figure[2] = lettre_U;
	figure[3] = lettre_X;
	figure[4] = lettre_L;
	figure[5] = lettre_H;
	figure[6] = lettre_D;
	figure[7] = lettre_O;
	figure[NEXEMPLE]=0;
	return figure;
}


Image** getImages(int& ne,int &ni, int& w,int &h)
{
	float** patterns = getPattern(ne,ni);

	Image** figure = (Image**) calloc(ne+1,sizeof(Image*));

    for(int k = 0; k < ne; k++) {
    	// create image object
    	figure[k] = new Image();
    	figure[k]->setData(patterns[k]);
    	figure[k]->setLabel('-');
        figure[k]->setDimensions(3, 3);
    }
	figure[ne]=0;

	w=3;
	h=3;

	return figure;
}

Image** getLearningPattern(int& ne,int &ni, int& w,int &h)
{
	return getImages(ne,ni,w,h);
}

Image** getReconnaissancePattern(int& ne,int &ni, int& w,int &h)
{
	return getImages(ne,ni,w,h);
}
