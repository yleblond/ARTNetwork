#include "artins.hpp"

#include "artin.hpp"
#include "artconst.hpp"

ARTInputLayer::ARTInputLayer(ARTNetwork* reseauART,int nE,int nS) : ARTCouche(reseauART)
{
	persistance    = I_PERSISTANCE; 		/* k_A1 	*/
	renforcement   = I_RENFORCEMENT;		/* k_F2_F1 	*/
	inhibation     = I_INHIBATION;			/* k_F1		*/
	autoInhibation = I_AUTOINHIBATION;		/* k_C1		*/
	plasticite     = I_PLASTICITE;			/* k_poids_F2_F1 */

	poidMinimum	   = (inhibation - 1.0 ) / renforcement;
	vigilance	   = I_VIGILANCE;			/* vigilance */

	CreerNeurones(nE, nS);
}

float ARTInputLayer::PoidAleatoire()
{
	return poidMinimum	+ (1.0 - poidMinimum) * RND01;
}

void ARTInputLayer::CreerNeurones(int nombre, int nombreS)
{
	neurones = new pNeurone[nombre+1];
	for(int i=0;i<nombre;i++)
		neurones[i]=new ARTInput(this,nombreS);
	neurones[nombre]=0;
}

void ARTInputLayer::AffecterEntree(float* figure)
{
	for (int i=0; neurones[i]; i++)
		((ARTInput*)neurones[i])->Entree(figure[i]);
}

int ARTInputLayer::NecessiteReset()
{
	int nEntreesActives=0;
	int nSortiesActives=0;

	for (int i=0; neurones[i]; i++)
	{
		if ( ((ARTInput*)neurones[i])->Entree()   > 0.0)
			nEntreesActives++;
		if ( neurones[i]->Sortie()   > 0.0)
			nSortiesActives++;
	}

	float q = (float)nSortiesActives / (float)nEntreesActives;

	return (q < vigilance) ? 1 : 0;
}

