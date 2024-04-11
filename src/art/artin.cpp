#include "artin.hpp"

#include "artins.hpp"
#include "artouts.hpp"
#include "artnet.hpp"


float ARTInput::CalculerInhibation()
{
//	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
//	float inhibation = 0;	/* Sigma(Sj) */
//	for (int j=0; coucheSortie->Neurone(j); j++)
//		inhibation = inhibation + coucheSortie->Neurone(j)->Sortie();
	return CoucheART()->ReseauART()->Outputs()->SortieTotale();
//	return inhibation;
}

float ARTInput::CalculerExitation()
{
	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
	float exitation = 0; 	/* Ei + k21 * Sigma(Sj.Pji) */
	for (int j=0; coucheSortie->Neurone(j); j++)
		exitation += coucheSortie->Neurone(j)->Sortie() * poids[j];
	exitation *= CoucheART()->Renforcement();
	exitation += entree;
	return exitation;
}

float ARTInput::CalculerActivite()
{
	activite += variationActivite;
	if (activite < 0.0 )
		activite = 0.0;
	if (activite > 1.0 )
		activite = 1.0;
	return activite;
}

void ARTInput::CalculerPoids()
{
	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
	int iR = coucheSortie->IndexRaisonnance();
	if (iR != -1)
		poids[iR ] += CoucheART()->Plasticite()
						*  coucheSortie->Neurone(iR)->Sortie()
						*  ( - poids[iR] + Sortie() );
}
