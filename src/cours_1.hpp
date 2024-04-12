#include <string.h>

#include "image.hpp"

#include "artsettings.hpp"
#include "prgsettings.hpp"

#include <iostream>
#include <fstream>


ARTSettings* getNetworkSettings() {
    ARTSettings* s = new ARTSettings();
    s->nOutputs = 8;
	s->WEIGHT_DISPLAY_THREESHOLD = 0.08;

	s->I_VIGILANCE = 0.97;
    
	return s;
}


ProcessSettings* getProcessSettings() {
    ProcessSettings* s = new ProcessSettings();
	s->LEARNING_LOOPS = 50;
	s->LEARNING_ITERATION = 500;
	s->QUERY_ITERATION = 40;
    return s;
}

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

float** getPattern()
{
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


ImageSet* getImages() {
	float** patterns = getPattern();

	Image** figure = (Image**) calloc(NEXEMPLE+1,sizeof(Image*));

    for(int k = 0; k < NEXEMPLE; k++) {
    	// create image object
    	figure[k] = new Image();
    	figure[k]->setData(patterns[k]);
    	figure[k]->setLabel('-');
        figure[k]->setDimensions(3, 3);
    }
	figure[NEXEMPLE]=0;

	ImageSet* set = new ImageSet();
	set->nEntrees = 9;
	set->nExemples = NEXEMPLE;
	set->imageSize = 9;
	set->width = 3;
    set->height = 3;
	set->learningFigure = figure;
	return set;

}

ImageSet* getLearningPattern()
{
	return getImages();
}

ImageSet* getReconnaissancePattern()
{
	return getImages();
}

