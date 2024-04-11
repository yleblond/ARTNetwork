#include "artout.hpp"

#include "artins.hpp"
#include "artouts.hpp"
#include "artnet.hpp"

#include <iostream>

void ARTOutput::UnReset()
{
	isReset = 0;
}

void ARTOutput::Reset()
{
	isReset = 1;
	activite = 0.0;
	Sortie(0.0);
}


float ARTOutput::CalculerSortie()
{
	if (isReset)
		return 0.0;
	return ARTNeurone::CalculerSortie();
}

float ARTOutput::CalculerInhibation()
{
	/* CALCUL DE L'INHIBATION */ /* -Aj + Sigma(Aj) */
/*	float inhibation = -Sortie();
	for (int j=0; Couche()->Neurone(j); j++)
		inhibation += Couche()->Neurone(j)->Sortie();*/

	return CoucheART()->SortieTotale()-Sortie();
/*	if (inhibation!=in2)
		std::cout << "(" << inhibation << " ; " << in2 << ")\n";

	return inhibation;*/
}

float ARTOutput::CalculerExitation()
{
	ARTInputLayer*   coucheEntree = CoucheART()->ReseauART()->Inputs();

	/* CALCUL DE L'EXITATION */ /* Aj + k12 * Sigma(Si.Pij) */
	float exitation = 0.0;
	for (int i=0; coucheEntree->Neurone(i); i++)
		exitation += poids[i] * coucheEntree->Neurone(i)->Sortie();
	exitation *= CoucheART()->Renforcement();
	exitation += activite;
	return exitation;
}

float ARTOutput::CalculerActivite()
{
	if (!isReset)
	{
		activite += variationActivite;
		if (activite<0.0)
			activite = 0.0;
	}
	return activite;
}

void ARTOutput::CalculerPoids()
{
	ARTInputLayer*   coucheEntree = CoucheART()->ReseauART()->Inputs();

	float sommeToutesEntres = coucheEntree->SortieTotale(); //0.0;
//	for (int i=0; coucheEntree->Neurone(i); i++)
//		sommeToutesEntres += coucheEntree->Neurone(i)->Sortie();

	for (int i=0; coucheEntree->Neurone(i); i++)
	{
		poids[i] +=
			CoucheART()->Plasticite()
			* Sortie()
			* ( 	( 1 - poids[i])
					* ((ARTOutputLayer*)CoucheART())->ContraintePlasticite()
					* coucheEntree->Neurone(i)->Sortie()
				- 	poids[i]
					* (	sommeToutesEntres
						- coucheEntree->Neurone(i)->Sortie()));
		if (poids[i] < 0.0)
			poids[i] = 0.0;
	}

}


