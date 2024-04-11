#ifndef HEADER_ART_INPUT
#define HEADER_ART_INPUT

#include "artneuro.hpp"

class ARTInput : public ARTNeurone
{
		float	entree;
	public:
		virtual void  Entree(float valeur) 	{ entree=valeur; };
		virtual float Entree() 				{ return entree; }
	private:
		virtual float CalculerInhibation();
		virtual float CalculerExitation();
	public:
		ARTInput(ARTCouche* pCouche, int nS) : ARTNeurone(pCouche,nS)
		{
			entree	 = 0.0;
		}

		virtual float  CalculerActivite();
		virtual void  CalculerPoids();
};


#endif
