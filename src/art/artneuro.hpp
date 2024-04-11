#ifndef HEADER_ART_GENERAL
#define HEADER_ART_GENERAL

#include "neuro.hpp"

class ARTCouche;
class ARTNetwork;
class ARTNeurone;
typedef ARTNeurone* pARTNeurone;

class ARTNeurone : public Neurone
{
	protected:
		float   variationActivite;
	public:
		virtual float CalculerInhibation();
		virtual float CalculerExitation();
	public:
		ARTNeurone(ARTCouche* pCouche, int nombreLiens);
		virtual ARTCouche* CoucheART()	    { return (ARTCouche*) Couche(); }
		virtual void Desactiver();
		virtual void CalculerVariation();
		virtual float CalculerActivite();
		virtual void CalculerPoids();
		virtual float CalculerSortie();
};


class ARTCouche : public CoucheNeurone
{
	protected:
		float activiteTotale;
		float sortieTotale;
	public:
		float ActiviteTotale() { return activiteTotale; }
		float SortieTotale() { return sortieTotale; }
	protected:
		float persistance;
		float renforcement;
		float inhibation;
		float autoInhibation;
		float plasticite;
	public:
		ARTCouche(ARTNetwork* reseauART);
	public:
		virtual void DesactiverNeurones();
		virtual void CalculerActivite();
		virtual void CalculerPoids();
	public:
		virtual float Persistance() 	{ return persistance; }
		virtual float Renforcement()	{ return renforcement; }
		virtual float Inhibation()		{ return inhibation; }
		virtual float AutoInhibation()	{ return autoInhibation; }
		virtual float Plasticite()		{ return plasticite; }
		virtual ARTNetwork* ReseauART()
		{
			return (ARTNetwork*) Reseau();
		}
		virtual ARTNeurone* NeuroneART(int i)
		{
			return (ARTNeurone*) Neurone(i);
		}
};

#endif
