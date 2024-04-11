#ifndef HEADER_NEURONE
#define HEADER_NEURONE

class Neurone;
typedef Neurone* pNeurone;
class CoucheNeurone;
class ReseauNeurone;

class Neurone
{
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
	public:
		virtual float Poids(int i) { return poids[i]; }

	private:
		CoucheNeurone*	couche;
	public:
		CoucheNeurone* Couche() { return couche; }
	public:
		Neurone(CoucheNeurone* pCouche, int nombreLiens);
		virtual ~Neurone();
		virtual void CreerLiens(int nombre);
};


class CoucheNeurone
{
	protected:
		pNeurone* neurones;
	private:
		ReseauNeurone*	reseau;
	public:
		CoucheNeurone(ReseauNeurone* r)
		{
			reseau=r;
			neurones=0;
		}
		virtual ~CoucheNeurone();
		virtual ReseauNeurone* Reseau()
		{
			return reseau;
		}
		virtual Neurone* Neurone(int i)
		{
			return neurones[i];
		}
		virtual float PoidAleatoire();
};

class ReseauNeurone
{
};

#endif
