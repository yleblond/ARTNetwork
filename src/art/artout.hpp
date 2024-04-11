#ifndef HEADER_ART_OUTPUT
#define HEADER_ART_OUTPUT

#include "artneuro.hpp"

class ARTOutput : public ARTNeurone
{
		int 	isReset;
	public:
		void Reset();
		void UnReset();
	private:
		virtual float CalculerInhibation();
		virtual float CalculerExitation();
	public:
		ARTOutput(ARTCouche* pCouche,int nE) : ARTNeurone(pCouche,nE) {}

		virtual float CalculerActivite();
		virtual void CalculerPoids();
		virtual float CalculerSortie();
};


#endif



