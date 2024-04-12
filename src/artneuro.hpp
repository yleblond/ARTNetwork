#ifndef HEADER_ART_GENERAL
#define HEADER_ART_GENERAL

#include "artsettings.hpp"

class ARTNeuron;
class ARTLayer;
class ARTNetwork;
typedef ARTNeuron* pARTNeuron;
#define RND01 ((float) ((float)rand() / (float)RAND_MAX))

class ARTNeuron
{
	private:
		ARTLayer*	layer;
	public:
		ARTLayer* Layer() { return layer; }

	private:
		float	sortie;
	public:
		virtual void  Sortie(float f) { sortie=f; }
		virtual float Sortie() { return sortie; }

	protected:
		float activite;
	public:
		virtual float Activite() { return activite; }

	protected:
		float*	poids;
		int 	nombrePoids;
	public:
		virtual float Poids(int i) { return poids[i]; }

	protected:
		float   variationActivite;
	public:
		virtual float CalculerInhibation();
		virtual float CalculerExitation();

	public:
		ARTNeuron(ARTLayer* pCouche, int nombreLiens);
		virtual ~ARTNeuron();
	
	public:
		virtual void Desactiver();
		virtual void CalculerVariation();
		virtual float CalculerActivite();
		virtual void CalculerPoids();
		virtual float CalculerSortie();
		virtual void CreerLiens(int nombre);
	public:
		void displayPoids(float threshold, int width);
};

class ARTInput : public ARTNeuron
{
		float	entree;
	public:
		virtual void  Entree(float valeur) 	{ entree=valeur; };
		virtual float Entree() 				{ return entree; }
	private:
		virtual float 	CalculerInhibation();
		virtual float 	CalculerExitation();
		virtual float  	CalculerActivite();
		virtual void  	CalculerPoids();
	public:
		ARTInput(ARTLayer* pCouche, int nS) : ARTNeuron(pCouche,nS)
		{
			entree	 = 0.0;
		}

};

class ARTOutput : public ARTNeuron
{
		int 	isReset;
	public:
		void Reset();
		void UnReset();
	private:
		virtual float CalculerInhibation();
		virtual float CalculerExitation();
	public:
		ARTOutput(ARTLayer* pCouche,int nE) : ARTNeuron(pCouche,nE) {}
	public:
		virtual float	CalculerActivite();
		virtual void 	CalculerPoids();
		virtual float 	CalculerSortie();
};

class ARTLayer 
{
	protected:
		ARTNeuron** neurons;

	protected:
		ARTNetwork*	network;
	public:
		virtual ARTNetwork* Network()
		{
			return network;
		}

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
		ARTLayer(ARTNetwork* reseauART);
		virtual ~ARTLayer();
	public:
		virtual void DesactiverNeurones();
		virtual void CalculerActivite();
		virtual void CalculerPoids();
		virtual float Persistance() 	{ return persistance; }
		virtual float Renforcement()	{ return renforcement; }
		virtual float Inhibation()		{ return inhibation; }
		virtual float AutoInhibation()	{ return autoInhibation; }
		virtual float Plasticite()		{ return plasticite; }
	public:
		virtual ARTNeuron* Neuron(int i) { return neurons[i]; }
		virtual float PoidAleatoire();
	public:
		void displayAllPoids(float threshold, int width);
};


class ARTInputLayer : public ARTLayer
{
	private:

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


class ARTOutputLayer : public ARTLayer
{
	private:
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

	public:
		ARTNeuron* BestMatch();
		void Display();

};

class ARTNetwork 
{
	public:
		ARTSettings*		settings;
	public:
		ARTInputLayer*		inputs;
		ARTOutputLayer*		outputs;
		float 				reactivite;
	public:
		ARTNetwork(ARTSettings* settings, int nEntrees,int nSorties);
		void Apprendre(float* figure,int nIteration);
		void Demander(float* figure,int nIteration);
		void Demarrer();
		void Calculer();
		void Iterer();
		void DisplayOutput();
	public:
		ARTInputLayer*		Inputs()	{ return inputs; }
		ARTOutputLayer*		Outputs()   { return outputs; }
		float 				Reactivite(){ return reactivite; }
};

#endif
