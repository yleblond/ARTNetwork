#include "neuro.hpp"
#include "debug.hpp"

Neurone::Neurone(CoucheNeurone* pCouche,int nombreLiens)
{
	activite = 0.0;
	sortie   = 0.0;
	couche = pCouche;
	poids=0;
	CreerLiens(nombreLiens);
}

Neurone::~Neurone()
{
	if (poids)
		delete [] poids;
}

void Neurone::CreerLiens(int nombre)
{
	if (nombre<1)
		return;
	poids = new float[nombre];
	for(int i=0;i<nombre;i++)
		poids[i] = couche->PoidAleatoire();
}

CoucheNeurone::~CoucheNeurone()
{
	if (neurones)
	{
		for (int i=0; neurones[i]; i++)
			delete neurones[i];
		delete [] neurones;
	}
}

float CoucheNeurone::PoidAleatoire()
{
	Erreur("ARTCouche::PoidAleatoire\n");
	return 0;
}
