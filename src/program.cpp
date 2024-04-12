#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>


#include "image.hpp"
#include "artneuro.hpp"
#include "shell.hpp"


#include "cours_mnist.hpp"
// #include "cours_2.hpp"

std::string getFloatArrayString(float data[], int size ) {
	std::string floatString;
	for(int i=0;i<size;i++) {
		floatString.append(std::to_string(data[i]));
		floatString.append(" ");
	}
	return floatString;
}

int main() {

	ImageSet* learningFigure = getLearningPattern();

	ARTSettings* artSettings = getNetworkSettings();
	ProcessSettings* prgSettings = getProcessSettings();

	ARTNetwork hello(artSettings, learningFigure->nEntrees, artSettings->nOutputs); 

	int usedInputsForTraining = learningFigure->nExemples;
	if (prgSettings->LEARNING_MAXITEMS>=0) {
		if (usedInputsForTraining > prgSettings->LEARNING_MAXITEMS) {
			usedInputsForTraining = prgSettings->LEARNING_MAXITEMS;
		}
	}

	std::cout << "Apprentisage\n" << usedInputsForTraining << " examples\n";

	for (int iter=0;iter<prgSettings->LEARNING_LOOPS;iter++) {
		for(int j=0;j< usedInputsForTraining;j++) {
			std::cout << "Apprentissage "<< j << "/" << usedInputsForTraining << " -> " << std::to_string(learningFigure->learningFigure[j]->getLabel()) << "\n";
			learningFigure->learningFigure[j]->display(0.5);
			hello.Apprendre(learningFigure->learningFigure[j]->getData(),prgSettings->LEARNING_ITERATION);
		}
	}

    std::string prompt;

	Attendre("Fin Apprentissage\n");

	hello.Outputs()->displayAllPoids(artSettings->WEIGHT_DISPLAY_THREESHOLD, learningFigure->width);

	Attendre("Launch Test\n");

	ImageSet* testFigure = getReconnaissancePattern();
	std::cout << "Reconnaissance\nEntries"  << testFigure->nEntrees << " ("<< learningFigure->nEntrees <<")\n";
	
	int usedInputsForTest =  testFigure->nExemples;
	if (prgSettings->QUERY_MAXITEMS>=0) {
		if (usedInputsForTest > prgSettings->QUERY_MAXITEMS) {
			usedInputsForTest = prgSettings->QUERY_MAXITEMS;
		}
	}

	std::cout << "Reconnaissance\n"  << usedInputsForTest << " examples\n";
	for(int i=0;i<usedInputsForTest;i++) {
		std::cout << "Reconnaissance " << i << "/" << usedInputsForTest << " -> " << std::to_string(testFigure->learningFigure[i]->getLabel()) <<"\n";;
		testFigure->learningFigure[i]->display(0.5);
		// std::cout << "\nInputLayer : " << getFloatArrayString(testFigure[i], nentrees);
		// std::cout << "\n";
		hello.Demander(testFigure->learningFigure[i]->getData(),prgSettings->QUERY_ITERATION);
		hello.DisplayOutput();
		std::cout << "\n";
		
		ARTNeuron* bestMatch = hello.Outputs()->BestMatch();
		if (bestMatch) {
			bestMatch->displayPoids(artSettings->WEIGHT_DISPLAY_THREESHOLD, testFigure->width);
		} 
				std::cout << "\n";
	}

	Attendre("Fin Reconnaissance\n");

	return 0;
}


