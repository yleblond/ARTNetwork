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
	// char buffer[100];
	// char outputbuffer[100];
	// strcpy(outputbuffer,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");


	int nTrainingExemples,nTrainingEntrees;
	int width,height;
	Image** learningFigure = getLearningPattern(nTrainingExemples,nTrainingEntrees, width, height);

	ARTNetwork hello(nTrainingEntrees,NSORTIES); 

	int usedInputsForTraining = nTrainingExemples;
	std::cout << "Apprentisage\n" << usedInputsForTraining << " examples\n";
	int cas;
	for (int iter=0;iter<LEARNING_LOOPS;iter++) {
		for(int j=0;j< usedInputsForTraining;j++) {
			std::cout << "Apprentissage "<< j << "/" << usedInputsForTraining << " -> " << std::to_string(learningFigure[j]->getLabel()) << "\n";
			learningFigure[j]->display(0.5);
			hello.Apprendre(learningFigure[j]->getData(),LEARNING_ITERATION);
		}
	}

    std::string prompt;

	Attendre("Fin Apprentissage\n");

	hello.Outputs()->displayAllPoids(WEIGHT_DISPLAY_THREESHOLD, width);

	Attendre("Launch Test\n");

	int nTestExemples,nTestEntrees;
	Image** testFigure = getReconnaissancePattern(nTestExemples,nTestEntrees, width, height);
	std::cout << "Reconnaissance\nEntries"  << nTestEntrees << " ("<< nTrainingEntrees <<")\n";
	
	int usedInputsForTest =  nTestExemples;

	std::cout << "Reconnaissance\n"  << usedInputsForTest << " examples\n";
	for(int i=0;i<usedInputsForTest;i++) {
		std::cout << "Reconnaissance " << i << "/" << usedInputsForTest << " -> " << std::to_string(testFigure[i]->getLabel()) <<"\n";;
		testFigure[i]->display(0.5);
		// std::cout << "\nInputLayer : " << getFloatArrayString(testFigure[i], nentrees);
		// std::cout << "\n";
		hello.Demander(testFigure[i]->getData(),QUERY_ITERATION);
		hello.DisplayOutput();
		
		ARTNeurone* bestMatch = hello.Outputs()->BestMatch();
		if (bestMatch) {
			bestMatch->displayPoids(WEIGHT_DISPLAY_THREESHOLD, width);
		} 
	}

	Attendre("Fin Reconnaissance\n");

	return 0;
}


