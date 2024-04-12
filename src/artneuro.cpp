#include "artneuro.hpp"

#include "shell.hpp"
#include <string>
#include <iostream>

// **********************************************************************
// IMPLEMENTATION ARTNeuron
// **********************************************************************

ARTNeuron::ARTNeuron(ARTLayer* pCouche,int nombreLiens)
{
	activite = 0.0;
	sortie   = 0.0;
	layer = pCouche;
	poids=0;
	CreerLiens(nombreLiens);
}

ARTNeuron::~ARTNeuron()
{
	if (poids)
		delete [] poids;
}


void ARTNeuron::CreerLiens(int nombre)
{
	if (nombre<1)
		return;
	
	nombrePoids = nombre;
	poids = new float[nombrePoids];
	for(int i=0;i<nombrePoids;i++) {
		poids[i] = layer->PoidAleatoire();
	}
}

void ARTNeuron::Desactiver()
{
	activite=0.0;
	Sortie(0.0);
}

float ARTNeuron::CalculerInhibation()
{
	Erreur("ARTNeuron::CalculerInhibation");
	return 0;
}

float ARTNeuron::CalculerExitation()
{
	Erreur("ARTNeuron::CalculerExitation");
	return 0;
}

void ARTNeuron::CalculerVariation()
{
	/* CALCUL DE LA SOMME DES ENTREES */
	float exitation  = CalculerExitation();
	float inhibation = CalculerInhibation();

	/* CALCUL DU D_ACTIVITE */
	variationActivite = Layer()->Network()->Reactivite()
	* (
	  - activite
	  + exitation  * (1- Layer()->Persistance() * activite)
	  - inhibation * (Layer()->Inhibation() + Layer()->AutoInhibation() * activite)
	  );
}

float ARTNeuron::CalculerActivite()
{
	Erreur("ARTNeuron::CalculerActivite");
	return 0.0;
}

float ARTNeuron::CalculerSortie()
{
	Sortie( (activite>0.0) ? 1.0 : 0.0 );
	return Sortie();
}

void ARTNeuron::CalculerPoids()
{
	Erreur("ARTNeuron::CalculerPoids");
}

void ARTNeuron::displayPoids(float threshold, int width) {
		for (int i = 0; i < nombrePoids; i++) {
			if (i%width) {
			} else {
				std::cout << "\n";
			}
			std::cout << ((poids[i] > threshold) ? "X" : " ");
		}
		std::cout << "\n";
	}

// **********************************************************************
// IMPLEMENTATION ARTLayer
// **********************************************************************


ARTLayer::ARTLayer(ARTNetwork* reseauART)
{
	network=reseauART;

	neurons=0;

	activiteTotale=0;
	sortieTotale=0;

	persistance    = 0; // DOIVENT ETRE EVALUEES PAR SOUS CLASSES
	renforcement   = 0;
	inhibation     = 0;
	autoInhibation = 0;
	plasticite     = 0;
}

ARTLayer::~ARTLayer()
{
	if (neurons)
	{
		for (int i=0; neurons[i]; i++)
			delete neurons[i];
		delete [] neurons;
	}
}

void ARTLayer::DesactiverNeurones()
{
	for (int i=0;Neuron(i);i++)
		Neuron(i)->Desactiver();
	activiteTotale=0;
	sortieTotale=0;
}

void ARTLayer::CalculerActivite()
{
	for (int i=0;Neuron(i);i++) {
		Neuron(i)->CalculerVariation();
	}

	activiteTotale=0;
	for (int j=0;Neuron(j);j++) {
		activiteTotale += Neuron(j)->CalculerActivite();
	}

	sortieTotale=0;
	for (int k=0;Neuron(k);k++) {
		sortieTotale   += Neuron(k)->CalculerSortie();
	}
}

void ARTLayer::CalculerPoids()
{
	for (int i=0;Neuron(i);i++)
		Neuron(i)->CalculerPoids();
}

float ARTLayer::PoidAleatoire()
{
	Erreur("ARTLayer::PoidAleatoire\n");
	return 0;
}

void ARTLayer::displayAllPoids(float threshold, int width) {
	std::cout << "displayAllPoids()\n";
	for (int i=0; neurons[i]; i++){
		std::cout << "Output("<< i <<")\n";
		neurons[i]->displayPoids( threshold, width);
		std::cout << "\n";
	}
}

// **********************************************************************
// IMPLEMENTATION ARTInput
// **********************************************************************

float ARTInput::CalculerInhibation()
{
//	ARTOutputLayer* coucheSortie = Layer()->Network()->Outputs();
//	float inhibation = 0;	/* Sigma(Sj) */
//	for (int j=0; coucheSortie->Neuron(j); j++)
//		inhibation = inhibation + coucheSortie->Neuron(j)->Sortie();
	return Layer()->Network()->Outputs()->SortieTotale();
//	return inhibation;
}

float ARTInput::CalculerExitation()
{
	ARTOutputLayer* coucheSortie = Layer()->Network()->Outputs();
	float exitation = 0; 	/* Ei + k21 * Sigma(Sj.Pji) */
	for (int j=0; coucheSortie->Neuron(j); j++)
		exitation += coucheSortie->Neuron(j)->Sortie() * poids[j];
	exitation *= Layer()->Renforcement();
	exitation += entree;
	return exitation;
}

float ARTInput::CalculerActivite()
{
	activite += variationActivite;
	if (activite < 0.0 )
		activite = 0.0;
	if (activite > 1.0 )
		activite = 1.0;
	return activite;
}

void ARTInput::CalculerPoids()
{
	ARTOutputLayer* coucheSortie = Layer()->Network()->Outputs();
	int iR = coucheSortie->IndexRaisonnance();
	if (iR != -1)
		poids[iR ] += Layer()->Plasticite()
						*  coucheSortie->Neuron(iR)->Sortie()
						*  ( - poids[iR] + Sortie() );
}


// **********************************************************************
// IMPLEMENTATION ARTInputLayer
// **********************************************************************


ARTInputLayer::ARTInputLayer(ARTNetwork* reseauART,int nE,int nS) : ARTLayer(reseauART)
{
	persistance    = reseauART->settings->I_PERSISTANCE; 		/* k_A1 	*/
	renforcement   = reseauART->settings->I_RENFORCEMENT;		/* k_F2_F1 	*/
	inhibation     = reseauART->settings->I_INHIBATION;			/* k_F1		*/
	autoInhibation = reseauART->settings->I_AUTOINHIBATION;		/* k_C1		*/
	plasticite     = reseauART->settings->I_PLASTICITE;			/* k_poids_F2_F1 */

	poidMinimum	   = (inhibation - 1.0 ) / renforcement;
	vigilance	   = reseauART->settings->I_VIGILANCE;			/* vigilance */

	CreerNeurones(nE, nS);
}

float ARTInputLayer::PoidAleatoire()
{
	return poidMinimum	+ (1.0 - poidMinimum) * RND01;
}

void ARTInputLayer::CreerNeurones(int nombre, int nombreS)
{
	neurons = new pARTNeuron[nombre+1];
	for(int i=0;i<nombre;i++)
		neurons[i]=new ARTInput(this,nombreS);
	neurons[nombre]=0;
}

void ARTInputLayer::AffecterEntree(float* figure)
{
	for (int i=0; neurons[i]; i++)
		((ARTInput*)neurons[i])->Entree(figure[i]);
}

int ARTInputLayer::NecessiteReset()
{
	int nEntreesActives=0;
	int nSortiesActives=0;

	for (int i=0; neurons[i]; i++)
	{
		if ( ((ARTInput*)neurons[i])->Entree()   > 0.0)
			nEntreesActives++;
		if ( neurons[i]->Sortie()   > 0.0)
			nSortiesActives++;
	}

	float q = (float)nSortiesActives / (float)nEntreesActives;

	return (q < vigilance) ? 1 : 0;
}



// **********************************************************************
// IMPLEMENTATION ARTOutput
// **********************************************************************

void ARTOutput::UnReset()
{
	isReset = 0;
}

void ARTOutput::Reset()
{
	isReset = 1;
	activite = 0.0;
	Sortie(0.0);
}


float ARTOutput::CalculerSortie()
{
	if (isReset)
		return 0.0;
	return ARTNeuron::CalculerSortie();
}

float ARTOutput::CalculerInhibation()
{
	/* CALCUL DE L'INHIBATION */ /* -Aj + Sigma(Aj) */
/*	float inhibation = -Sortie();
	for (int j=0; Layer()->Neuron(j); j++)
		inhibation += Layer()->Neuron(j)->Sortie();*/

	return Layer()->SortieTotale()-Sortie();
/*	if (inhibation!=in2)
		std::cout << "(" << inhibation << " ; " << in2 << ")\n";

	return inhibation;*/
}

float ARTOutput::CalculerExitation()
{
	ARTInputLayer*   coucheEntree = Layer()->Network()->Inputs();

	/* CALCUL DE L'EXITATION */ /* Aj + k12 * Sigma(Si.Pij) */
	float exitation = 0.0;
	for (int i=0; coucheEntree->Neuron(i); i++)
		exitation += poids[i] * coucheEntree->Neuron(i)->Sortie();
	exitation *= Layer()->Renforcement();
	exitation += activite;
	return exitation;
}

float ARTOutput::CalculerActivite()
{
	if (!isReset)
	{
		activite += variationActivite;
		if (activite<0.0)
			activite = 0.0;
	}
	return activite;
}

void ARTOutput::CalculerPoids()
{
	ARTInputLayer*   coucheEntree = Layer()->Network()->Inputs();

	float sommeToutesEntres = coucheEntree->SortieTotale(); //0.0;
//	for (int i=0; coucheEntree->Neuron(i); i++)
//		sommeToutesEntres += coucheEntree->Neuron(i)->Sortie();

	for (int i=0; coucheEntree->Neuron(i); i++)
	{
		poids[i] +=
			Layer()->Plasticite()
			* Sortie()
			* ( 	( 1 - poids[i])
					* ((ARTOutputLayer*)Layer())->ContraintePlasticite()
					* coucheEntree->Neuron(i)->Sortie()
				- 	poids[i]
					* (	sommeToutesEntres
						- coucheEntree->Neuron(i)->Sortie()));
		if (poids[i] < 0.0)
			poids[i] = 0.0;
	}

}




// **********************************************************************
// IMPLEMENTATION ARTOutputLayer
// **********************************************************************


ARTOutputLayer::ARTOutputLayer(ARTNetwork* reseauART, int nS, int nE) : ARTLayer(reseauART)
{

	persistance    		= reseauART->settings->O_PERSISTANCE; 		/* k_A2 				*/
	renforcement   		= reseauART->settings->O_RENFORCEMENT;		/* k_F1_F2 				*/
	inhibation     		= reseauART->settings->O_INHIBATION;			/* k_inhibe_F2			*/
	autoInhibation 		= reseauART->settings->O_AUTOINHIBATION;		/* k_C2					*/
	contraintePlasticite= reseauART->settings->O_CONTRAINTE_PLASTICITE; /* k_F1_Poids_F1_F2		*/

	poidMaximum = contraintePlasticite
					  / ( contraintePlasticite  - 1.0  + (float)nE	);
	plasticite 	   =  renforcement * poidMaximum / 2.0; /* calcule de k_Poids_F1_F2		*/

	CreerNeurones(nS,nE);
}

float ARTOutputLayer::PoidAleatoire()
{
	return poidMaximum * RND01;
}

void ARTOutputLayer::CreerNeurones(int nombre, int nombreE)
{
	neurons = new pARTNeuron[nombre+1];

	for(int i=0;i<nombre;i++) {
		neurons[i]=new ARTOutput(this,nombreE);
	}
	neurons[nombre]=0;
}

void ARTOutputLayer::UnReset()
{
	for (int i=0; neurons[i]; i++) {
		((ARTOutput*)neurons[i])->UnReset();
	}
}

void ARTOutputLayer::DesactiverNeurones()
{
	ARTLayer::DesactiverNeurones();
	neuroneRaisonnance = 0;
	iRaisonnance=-1;
}

void ARTOutputLayer::CalculerActivite()
{
	ARTLayer::CalculerActivite();

	float valeurRaisonnance = -0.00001;
	iRaisonnance = -1;
	neuroneRaisonnance = (ARTOutput*) 0;

	for (int i=0; neurons[i]; i++) {
		if ( neurons[i]->Activite() > valeurRaisonnance) {
			neuroneRaisonnance = (ARTOutput*) neurons[i];
			valeurRaisonnance = neurons[i]->Activite();
			iRaisonnance = i;
		}
	}

//	std::cout << " " << iRaisonnance;

}

void ARTOutputLayer::SortieBinaire()
{
	for (int i=0; neurons[i]; i++)
		neurons[i]->Sortie(0.0);

	if (neuroneRaisonnance)
	{
		neuroneRaisonnance->Sortie(1.0);
		sortieTotale=1.0;
	}
	else
		sortieTotale=0.0;
}


void ARTOutputLayer::ResetRaisonnance()
{
	if (!neuroneRaisonnance)
		return;
	sortieTotale -= neuroneRaisonnance->Sortie();
	neuroneRaisonnance->Reset();
}


void ARTOutputLayer::Display() {
	std::string floatString;
	std::string resultString;

	for (int i=0; neurons[i]; i++){
		floatString.append(std::to_string(neurons[i]->Sortie()));
		floatString.append(" ");
		if (neurons[i]->Sortie()>0.9) {
			resultString += std::to_string(i);
			resultString += " ";
		}
	}
	std::cout << "=>\n";
	// std::cout << "OutputLayer " << floatString << "\n";
	std::cout << "Answer " << resultString << "\n";
}

ARTNeuron* ARTOutputLayer::BestMatch() {
	float bestResult = 0;
	int bestNeurone = -1;

	for (int i=0; neurons[i]; i++){
		float result = neurons[i]->Sortie();

		if (result>0.9) {
			if (result > bestResult) {
				bestResult = neurons[i]->Sortie();
				bestNeurone = i;
			}
		}
	}

	if (bestNeurone>=0) {
		return neurons[bestNeurone];
	} else {
		return 0;
	}
}

// **********************************************************************
// IMPLEMENTATION ARTNetwork
// **********************************************************************

ARTNetwork::ARTNetwork( ARTSettings* s,int nEntrees,int nSorties)
{
	settings = s;
	
	reactivite = settings->N_REACTIVITE;

	inputs	= new ARTInputLayer(this, nEntrees, nSorties);
	outputs	= new ARTOutputLayer(this, nSorties, nEntrees);
}


void ARTNetwork::Apprendre(float* figure, int nIteration)
{
	inputs->AffecterEntree(figure);
	Demarrer();
	for (int i=0;i<nIteration;i++) {
		Iterer();
	}
}

void ARTNetwork::Demander(float* figure,int nIteration)
{
	inputs->AffecterEntree(figure);
	Demarrer();
	for (int i=0;i<nIteration;i++) {
		Calculer();
	}
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

	if (inputs->NecessiteReset()) {
		outputs->ResetRaisonnance();
	} else {
		outputs->CalculerPoids();
		inputs->CalculerPoids();
	}
	outputs->CalculerActivite();
	outputs->SortieBinaire();
}

void ARTNetwork::Calculer()
{
	inputs->CalculerActivite();
	if (inputs->NecessiteReset()) {
		outputs->ResetRaisonnance();
	}
	outputs->CalculerActivite();
	outputs->SortieBinaire();
}


void ARTNetwork::DisplayOutput() {
	outputs->Display();
}