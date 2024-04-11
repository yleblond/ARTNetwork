#include "artouts.hpp"

#include "artconst.hpp"

#include <iostream>
#include <string>

ARTOutputLayer::ARTOutputLayer(ARTNetwork* reseauART, int nS, int nE) : ARTCouche(reseauART)
{
	persistance    		= O_PERSISTANCE; 		/* k_A2 				*/
	renforcement   		= O_RENFORCEMENT;		/* k_F1_F2 				*/
	inhibation     		= O_INHIBATION;			/* k_inhibe_F2			*/
	autoInhibation 		= O_AUTOINHIBATION;		/* k_C2					*/
	contraintePlasticite= O_CONTRAINTE_PLASTICITE; /* k_F1_Poids_F1_F2		*/

	poidMaximum = contraintePlasticite
					  / ( contraintePlasticite  - 1.0  + (float)nE	);
	plasticite 	   =  renforcement * poidMaximum / 2.0; /* calcule de k_Poids_F1_F2		*/

	CreerNeurones(nS,nE);
}

float ARTOutputLayer::PoidAleatoire()
{
	return poidMaximum * RND01;
}

void ARTOutputLayer::CreerNeurones(int nombre, int nombreE)
{
	neurones = new pNeurone[nombre+1];

	for(int i=0;i<nombre;i++)
		neurones[i]=new ARTOutput(this,nombreE);
	neurones[nombre]=0;
}

void ARTOutputLayer::UnReset()
{
	for (int i=0; neurones[i]; i++)
		((ARTOutput*)neurones[i])->UnReset();
}

void ARTOutputLayer::DesactiverNeurones()
{
	ARTCouche::DesactiverNeurones();
	neuroneRaisonnance = 0;
	iRaisonnance=-1;
}

void ARTOutputLayer::CalculerActivite()
{
	ARTCouche::CalculerActivite();

	float valeurRaisonnance = -0.00001;
	iRaisonnance = -1;
	neuroneRaisonnance = (ARTOutput*) 0;

	for (int i=0; neurones[i]; i++)
		if ( neurones[i]->Activite() > valeurRaisonnance)
		{
			neuroneRaisonnance = (ARTOutput*) neurones[i];
			valeurRaisonnance = neurones[i]->Activite();
			iRaisonnance = i;
		}

//	std::cout << " " << iRaisonnance;

}

void ARTOutputLayer::SortieBinaire()
{
	for (int i=0; neurones[i]; i++)
		neurones[i]->Sortie(0.0);

	if (neuroneRaisonnance)
	{
		neuroneRaisonnance->Sortie(1.0);
		sortieTotale=1.0;
	}
	else
		sortieTotale=0.0;
}


void ARTOutputLayer::ResetRaisonnance()
{
	if (!neuroneRaisonnance)
		return;
	sortieTotale -= neuroneRaisonnance->Sortie();
	neuroneRaisonnance->Reset();
}


void ARTOutputLayer::Display(char* buffer) {
	std::string floatString;
	std::string resultString;

	for (int i=0; neurones[i]; i++){
		floatString.append(std::to_string(neurones[i]->Sortie()));
		floatString.append(" ");
		if (neurones[i]->Sortie()>0.9) {
			resultString += std::to_string(i);
			resultString += " ";
		}
	}
	std::cout << "=>\n";
	// std::cout << "OutputLayer " << floatString << "\n";
	std::cout << "Answer " << resultString << "\n";
}




