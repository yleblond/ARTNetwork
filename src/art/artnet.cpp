

#include "artnet.hpp"

#include "artins.hpp"
#include "artouts.hpp"
#include "artconst.hpp"

#include <iostream>

/* IMPLEMENTATION */

ARTNetwork::ARTNetwork(int nEntrees,int nSorties)
{
	reactivite = N_REACTIVITE;

	inputs	= new ARTInputLayer(this, nEntrees, nSorties);
	outputs	= new ARTOutputLayer(this, nSorties, nEntrees);
}


void ARTNetwork::Apprendre(float* figure, int nIteration)
{
	inputs->AffecterEntree(figure);
	Demarrer();
	for (int i=0;i<nIteration;i++)
		Iterer();
}

void ARTNetwork::Demander(float* figure,int nIteration)
{
	inputs->AffecterEntree(figure);
	Demarrer();
	for (int i=0;i<nIteration;i++)
		Calculer();
}

void ARTNetwork::Demarrer()
{
	outputs->UnReset();
	outputs->DesactiverNeurones();
	inputs->DesactiverNeurones();
	inputs->CalculerActivite();
	outputs->CalculerActivite();
	outputs->SortieBinaire();
}

void ARTNetwork::Iterer()
{
	inputs->CalculerActivite();

	if (inputs->NecessiteReset())
		outputs->ResetRaisonnance();
	else
	{
		outputs->CalculerPoids();
		inputs->CalculerPoids();
	}
	outputs->CalculerActivite();
	outputs->SortieBinaire();
}

void ARTNetwork::Calculer()
{
	inputs->CalculerActivite();
	if (inputs->NecessiteReset())
		outputs->ResetRaisonnance();
	outputs->CalculerActivite();
	outputs->SortieBinaire();
}


void ARTNetwork::DisplayOutput(char* buffer) {
	outputs->Display( buffer);
}


