#ifndef HEADER_ART_INPUTLAYER
#define HEADER_ART_INPUTLAYER

#include "artneuro.hpp"

class ARTInputLayer : public ARTCouche
{
		float vigilance;
		float poidMinimum;

		virtual void CreerNeurones(int nombre, int nombreS);
	public:
		ARTInputLayer(ARTNetwork* reseauART,int nEntree,int nSortie);
		void AffecterEntree(float* figure);
		int  NecessiteReset();
	public:
		float Vigilance()		{ return vigilance; }
		float PoidMinimum()		{ return poidMinimum; }
		virtual float PoidAleatoire();
};

#endif