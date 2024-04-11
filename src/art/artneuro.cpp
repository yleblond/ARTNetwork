#include "artneuro.hpp"
#include "artnet.hpp"

#include "debug.hpp"

ARTNeurone::ARTNeurone(ARTCouche* pCouche,int nombreLiens) : Neurone(pCouche,nombreLiens)
{
}

void ARTNeurone::Desactiver()
{
	activite=0.0;
	Sortie(0.0);
}

float ARTNeurone::CalculerInhibation()
{
	Erreur("ARTNeurone::CalculerInhibation");
	return 0;
}

float ARTNeurone::CalculerExitation()
{
	Erreur("ARTNeurone::CalculerExitation");
	return 0;
}

void ARTNeurone::CalculerVariation()
{
	/* CALCUL DE LA SOMME DES ENTREES */
	float exitation  = CalculerExitation();
	float inhibation = CalculerInhibation();

	/* CALCUL DU D_ACTIVITE */
	variationActivite = CoucheART()->ReseauART()->Reactivite()
	* (
	  - activite
	  + exitation  * (1- CoucheART()->Persistance() * activite)
	  - inhibation * (CoucheART()->Inhibation() + CoucheART()->AutoInhibation() * activite)
	  );
}

float ARTNeurone::CalculerActivite()
{
	Erreur("ARTNeurone::CalculerActivite");
	return 0.0;
}

float ARTNeurone::CalculerSortie()
{
	Sortie( (activite>0.0) ? 1.0 : 0.0 );
	return Sortie();
}

void ARTNeurone::CalculerPoids()
{
	Erreur("ARTNeurone::CalculerPoids");
}


// **********************************************************************
// **********************************************************************
// **********************************************************************


ARTCouche::ARTCouche(ARTNetwork* reseauART)
	: CoucheNeurone(reseauART)
{
	activiteTotale=0;
	sortieTotale=0;

	persistance    = 0; // DOIVENT ETRE EVALUEES PAR SOUS CLASSES
	renforcement   = 0;
	inhibation     = 0;
	autoInhibation = 0;
	plasticite     = 0;
}

void ARTCouche::DesactiverNeurones()
{
	for (int i=0;Neurone(i);i++)
		NeuroneART(i)->Desactiver();
	activiteTotale=0;
	sortieTotale=0;
}

void ARTCouche::CalculerActivite()
{
	for (int i=0;Neurone(i);i++)
		NeuroneART(i)->CalculerVariation();

	activiteTotale=0;
	for (int j=0;Neurone(j);j++)
		activiteTotale += NeuroneART(j)->CalculerActivite();

	sortieTotale=0;
	for (int k=0;Neurone(k);k++)
		sortieTotale   += NeuroneART(k)->CalculerSortie();
}

void ARTCouche::CalculerPoids()
{
	for (int i=0;Neurone(i);i++)
		NeuroneART(i)->CalculerPoids();
}

