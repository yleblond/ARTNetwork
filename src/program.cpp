#include "art/artconst.hpp"
#include "art/artnet.hpp"

//#include "cours_mnist.hpp"

#include "cours_mnist.hpp"
#include "art/image.hpp"
// #include "cours_2.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>


std::string Attendre(const char* s)
{
	std::string texte;
	std::cout << "\n" << s << "\n";
	std::getline(std::cin, texte);
	return texte;
}

int Random(int max)
{
	float f=(float)max * RND01;
	return f;
}

std::string getFloatArrayString(float data[], int size ) {
	std::string floatString;
	for(int i=0;i<size;i++) {
		floatString.append(std::to_string(data[i]));
		floatString.append(" ");
	}
	return floatString;
}

int main() {
	char buffer[100];
	char outputbuffer[100];
	strcpy(outputbuffer,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");


	int nTrainingExemples,nTrainingEntrees;
	Image** learningFigure = getLearningPattern(nTrainingExemples,nTrainingEntrees);

	ARTNetwork hello(nTrainingEntrees,nTrainingEntrees /*11*/);

	int usedInputsForTraining = 10000; //nTrainingExemples;
	std::cout << "\nApprentisage\n" << usedInputsForTraining << " examples\n";
	int cas;
	for(int j=0;j< usedInputsForTraining;j++)
	{
		std::cout << "\nApprentissage "<< j << "/" << usedInputsForTraining << " -> " << std::to_string(learningFigure[j]->getLabel());
		// std::cout << "\nInputLayer :" << getFloatArrayString(learningFigure[j], nentrees);
		std::cout << "\n";
		hello.Apprendre(learningFigure[j]->getData(),40);
	}

    std::string prompt;

	Attendre("\nFin Apprentissage\n");

	int nTestExemples,nTestEntrees;
	Image** testFigure = getReconnaissancePattern(nTestExemples,nTestEntrees);
	std::cout << "\nReconnaissance\nEntries"  << nTestEntrees << " ("<< nTrainingEntrees <<")\n";
	
	int usedInputsForTest = nTestExemples;

	std::cout << "\nReconnaissance\n"  << usedInputsForTest << " examples\n";
	for(int i=0;i<usedInputsForTest;i++) {
		std::cout << "\nReconnaissance " << i << "/" << usedInputsForTest << " -> " << std::to_string(learningFigure[i]->getLabel());
		// std::cout << "\nInputLayer : " << getFloatArrayString(testFigure[i], nentrees);
		std::cout << "\n";
		hello.Demander(testFigure[i]->getData(),40);
		hello.DisplayOutput(outputbuffer);
		
	}

	Attendre("\nFin Reconnaissance\n");

	return 0;
}


