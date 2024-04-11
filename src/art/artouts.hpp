#ifndef HEADER_ART_OUTPUTLAYER
#define HEADER_ART_OUTPUTLAYER

#include "artneuro.hpp"
#include "artout.hpp"

class ARTOutputLayer : public ARTCouche
{
		float contraintePlasticite;
		float poidMaximum;

		int iRaisonnance;
		ARTOutput* neuroneRaisonnance;

		void CreerNeurones(int nombre, int nombreE);
	public:
		ARTOutputLayer(ARTNetwork* reseauART,int nombre, int nombreE);
		virtual void CalculerActivite();
		virtual void DesactiverNeurones();

		void SortieBinaire();
		void UnReset();
		void ResetRaisonnance();
	public:
		ARTOutput* NeuroneRaisonnance() { return neuroneRaisonnance; }
		int IndexRaisonnance() { return iRaisonnance; }
		float ContraintePlasticite()     { return contraintePlasticite; }
		float PoidMaximum()              { return poidMaximum; }
		virtual float PoidAleatoire();

		void Display(char* buffer);

};

#endif
