#ifndef HEADER_ART_GENERAL
#define HEADER_ART_GENERAL

class ARTCouche;
class ARTNetwork;
class ARTNeurone;
typedef ARTNeurone* pARTNeurone;

#define I_PERSISTANCE 		0.0
#define I_RENFORCEMENT 		1.9
#define I_INHIBATION 		2.1
#define I_AUTOINHIBATION 	0.0
#define I_VIGILANCE 		0.7 // 0.97
#define I_PLASTICITE 		0.035

#define O_PERSISTANCE 		0.0
#define O_RENFORCEMENT 		1.6
#define O_INHIBATION 		2.2
#define O_AUTOINHIBATION 	0.0
#define O_CONTRAINTE_PLASTICITE 1.4

#define N_ITERATIONS		25
#define N_REACTIVITE		0.1

#define RND01 ((float) ((float)rand() / (float)RAND_MAX))


class ARTNeurone
{
	private:
		ARTCouche*	couche;
	public:
		ARTCouche* Couche() { return couche; }

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
		ARTNeurone(ARTCouche* pCouche, int nombreLiens);
		virtual ~ARTNeurone();
	
	public:
		virtual ARTCouche* CoucheART()	    { return (ARTCouche*) Couche(); }
		virtual void Desactiver();
		virtual void CalculerVariation();
		virtual float CalculerActivite();
		virtual void CalculerPoids();
		virtual float CalculerSortie();
		virtual void CreerLiens(int nombre);
	public:
		void displayPoids(float threshold, int width);
};

class ARTInput : public ARTNeurone
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
		ARTInput(ARTCouche* pCouche, int nS) : ARTNeurone(pCouche,nS)
		{
			entree	 = 0.0;
		}

};

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
	public:
		virtual float	CalculerActivite();
		virtual void 	CalculerPoids();
		virtual float 	CalculerSortie();
};

class ARTCouche 
{
	protected:
		ARTNeurone** neurones;

	protected:
		ARTNetwork*	reseau;
	public:
		virtual ARTNetwork* ReseauART()
		{
			return (ARTNetwork*) reseau;
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
		ARTCouche(ARTNetwork* reseauART);
		virtual ~ARTCouche();
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
		virtual ARTNeurone* NeuroneART(int i)
		{
			return (ARTNeurone*) Neurone(i);
		}
	public:
		virtual ARTNeurone* Neurone(int i)
		{
			return neurones[i];
		}
		virtual float PoidAleatoire();
	public:
		void displayAllPoids(float threshold, int width);
};


class ARTInputLayer : public ARTCouche
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


class ARTOutputLayer : public ARTCouche
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
		ARTNeurone* BestMatch();
		void Display();

};

class ARTNetwork 
{
		ARTInputLayer*		inputs;
		ARTOutputLayer*		outputs;
		float 				reactivite;
	public:
		ARTNetwork(int nEntrees,int nSorties);
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
