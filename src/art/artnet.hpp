#ifndef HEADER_ART_NETWORK
#define HEADER_ART_NETWORK

#include "neuro.hpp"

#include "artins.hpp"
#include "artouts.hpp"

class ARTNetwork : public ReseauNeurone
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
		void DisplayOutput(char* buffer);
	public:
		ARTInputLayer*		Inputs()	{ return inputs; }
		ARTOutputLayer*		Outputs()   { return outputs; }
		float 				Reactivite(){ return reactivite; }
};

#endif


