#include "artneuro.hpp"

#include "shell.hpp"
#include <string>
#include <iostream>

// **********************************************************************
// IMPLEMENTATION ARTNeurone
// **********************************************************************

ARTNeurone::ARTNeurone(ARTCouche* pCouche,int nombreLiens)
{
	activite = 0.0;
	sortie   = 0.0;
	couche = pCouche;
	poids=0;
	CreerLiens(nombreLiens);
}

ARTNeurone::~ARTNeurone()
{
	if (poids)
		delete [] poids;
}


void ARTNeurone::CreerLiens(int nombre)
{
	if (nombre<1)
		return;
	
	nombrePoids = nombre;
	poids = new float[nombrePoids];
	for(int i=0;i<nombrePoids;i++) {
		poids[i] = couche->PoidAleatoire();
	}
}

void ARTNeurone::Desactiver()
{
	activite=0.0;
	Sortie(0.0);
}

float ARTNeurone::CalculerInhibation()
{
	Erreur("ARTNeurone::CalculerInhibation");
	return 0;
}

float ARTNeurone::CalculerExitation()
{
	Erreur("ARTNeurone::CalculerExitation");
	return 0;
}

void ARTNeurone::CalculerVariation()
{
	/* CALCUL DE LA SOMME DES ENTREES */
	float exitation  = CalculerExitation();
	float inhibation = CalculerInhibation();

	/* CALCUL DU D_ACTIVITE */
	variationActivite = CoucheART()->ReseauART()->Reactivite()
	* (
	  - activite
	  + exitation  * (1- CoucheART()->Persistance() * activite)
	  - inhibation * (CoucheART()->Inhibation() + CoucheART()->AutoInhibation() * activite)
	  );
}

float ARTNeurone::CalculerActivite()
{
	Erreur("ARTNeurone::CalculerActivite");
	return 0.0;
}

float ARTNeurone::CalculerSortie()
{
	Sortie( (activite>0.0) ? 1.0 : 0.0 );
	return Sortie();
}

void ARTNeurone::CalculerPoids()
{
	Erreur("ARTNeurone::CalculerPoids");
}

void ARTNeurone::displayPoids(float threshold, int width) {
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
// IMPLEMENTATION ARTCouche
// **********************************************************************


ARTCouche::ARTCouche(ARTNetwork* reseauART)
{
	reseau=reseauART;

	neurones=0;

	activiteTotale=0;
	sortieTotale=0;

	persistance    = 0; // DOIVENT ETRE EVALUEES PAR SOUS CLASSES
	renforcement   = 0;
	inhibation     = 0;
	autoInhibation = 0;
	plasticite     = 0;
}

ARTCouche::~ARTCouche()
{
	if (neurones)
	{
		for (int i=0; neurones[i]; i++)
			delete neurones[i];
		delete [] neurones;
	}
}

void ARTCouche::DesactiverNeurones()
{
	for (int i=0;Neurone(i);i++)
		NeuroneART(i)->Desactiver();
	activiteTotale=0;
	sortieTotale=0;
}

void ARTCouche::CalculerActivite()
{
	for (int i=0;Neurone(i);i++) {
		NeuroneART(i)->CalculerVariation();
	}

	activiteTotale=0;
	for (int j=0;Neurone(j);j++) {
		activiteTotale += NeuroneART(j)->CalculerActivite();
	}

	sortieTotale=0;
	for (int k=0;Neurone(k);k++) {
		sortieTotale   += NeuroneART(k)->CalculerSortie();
	}
}

void ARTCouche::CalculerPoids()
{
	for (int i=0;Neurone(i);i++)
		NeuroneART(i)->CalculerPoids();
}

float ARTCouche::PoidAleatoire()
{
	Erreur("ARTCouche::PoidAleatoire\n");
	return 0;
}

void ARTCouche::displayAllPoids(float threshold, int width) {
	std::cout << "displayAllPoids()\n";
	for (int i=0; neurones[i]; i++){
		std::cout << "Output("<< i <<")\n";
		neurones[i]->displayPoids( threshold, width);
		std::cout << "\n";
	}
}

// **********************************************************************
// IMPLEMENTATION ARTInput
// **********************************************************************

float ARTInput::CalculerInhibation()
{
//	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
//	float inhibation = 0;	/* Sigma(Sj) */
//	for (int j=0; coucheSortie->Neurone(j); j++)
//		inhibation = inhibation + coucheSortie->Neurone(j)->Sortie();
	return CoucheART()->ReseauART()->Outputs()->SortieTotale();
//	return inhibation;
}

float ARTInput::CalculerExitation()
{
	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
	float exitation = 0; 	/* Ei + k21 * Sigma(Sj.Pji) */
	for (int j=0; coucheSortie->Neurone(j); j++)
		exitation += coucheSortie->Neurone(j)->Sortie() * poids[j];
	exitation *= CoucheART()->Renforcement();
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
	ARTOutputLayer* coucheSortie = CoucheART()->ReseauART()->Outputs();
	int iR = coucheSortie->IndexRaisonnance();
	if (iR != -1)
		poids[iR ] += CoucheART()->Plasticite()
						*  coucheSortie->Neurone(iR)->Sortie()
						*  ( - poids[iR] + Sortie() );
}


// **********************************************************************
// IMPLEMENTATION ARTInputLayer
// **********************************************************************


ARTInputLayer::ARTInputLayer(ARTNetwork* reseauART,int nE,int nS) : ARTCouche(reseauART)
{
	persistance    = I_PERSISTANCE; 		/* k_A1 	*/
	renforcement   = I_RENFORCEMENT;		/* k_F2_F1 	*/
	inhibation     = I_INHIBATION;			/* k_F1		*/
	autoInhibation = I_AUTOINHIBATION;		/* k_C1		*/
	plasticite     = I_PLASTICITE;			/* k_poids_F2_F1 */

	poidMinimum	   = (inhibation - 1.0 ) / renforcement;
	vigilance	   = I_VIGILANCE;			/* vigilance */

	CreerNeurones(nE, nS);
}

float ARTInputLayer::PoidAleatoire()
{
	return poidMinimum	+ (1.0 - poidMinimum) * RND01;
}

void ARTInputLayer::CreerNeurones(int nombre, int nombreS)
{
	neurones = new pARTNeurone[nombre+1];
	for(int i=0;i<nombre;i++)
		neurones[i]=new ARTInput(this,nombreS);
	neurones[nombre]=0;
}

void ARTInputLayer::AffecterEntree(float* figure)
{
	for (int i=0; neurones[i]; i++)
		((ARTInput*)neurones[i])->Entree(figure[i]);
}

int ARTInputLayer::NecessiteReset()
{
	int nEntreesActives=0;
	int nSortiesActives=0;

	for (int i=0; neurones[i]; i++)
	{
		if ( ((ARTInput*)neurones[i])->Entree()   > 0.0)
			nEntreesActives++;
		if ( neurones[i]->Sortie()   > 0.0)
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
	return ARTNeurone::CalculerSortie();
}

float ARTOutput::CalculerInhibation()
{
	/* CALCUL DE L'INHIBATION */ /* -Aj + Sigma(Aj) */
/*	float inhibation = -Sortie();
	for (int j=0; Couche()->Neurone(j); j++)
		inhibation += Couche()->Neurone(j)->Sortie();*/

	return CoucheART()->SortieTotale()-Sortie();
/*	if (inhibation!=in2)
		std::cout << "(" << inhibation << " ; " << in2 << ")\n";

	return inhibation;*/
}

float ARTOutput::CalculerExitation()
{
	ARTInputLayer*   coucheEntree = CoucheART()->ReseauART()->Inputs();

	/* CALCUL DE L'EXITATION */ /* Aj + k12 * Sigma(Si.Pij) */
	float exitation = 0.0;
	for (int i=0; coucheEntree->Neurone(i); i++)
		exitation += poids[i] * coucheEntree->Neurone(i)->Sortie();
	exitation *= CoucheART()->Renforcement();
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
	ARTInputLayer*   coucheEntree = CoucheART()->ReseauART()->Inputs();

	float sommeToutesEntres = coucheEntree->SortieTotale(); //0.0;
//	for (int i=0; coucheEntree->Neurone(i); i++)
//		sommeToutesEntres += coucheEntree->Neurone(i)->Sortie();

	for (int i=0; coucheEntree->Neurone(i); i++)
	{
		poids[i] +=
			CoucheART()->Plasticite()
			* Sortie()
			* ( 	( 1 - poids[i])
					* ((ARTOutputLayer*)CoucheART())->ContraintePlasticite()
					* coucheEntree->Neurone(i)->Sortie()
				- 	poids[i]
					* (	sommeToutesEntres
						- coucheEntree->Neurone(i)->Sortie()));
		if (poids[i] < 0.0)
			poids[i] = 0.0;
	}

}




// **********************************************************************
// IMPLEMENTATION ARTOutputLayer
// **********************************************************************


ARTOutputLayer::ARTOutputLayer(ARTNetwork* reseauART, int nS, int nE) : ARTCouche(reseauART)
{

	persistance    		= O_PERSISTANCE; 		/* k_A2 				*/
	renforcement   		= O_RENFORCEMENT;		/* k_F1_F2 				*/
	inhibation     		= O_INHIBATION;			/* k_inhibe_F2			*/
	autoInhibation 		= O_AUTOINHIBATION;		/* k_C2					*/
	contraintePlasticite= O_CONTRAINTE_PLASTICITE; /* k_F1_Poids_F1_F2		*/

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
	neurones = new pARTNeurone[nombre+1];

	for(int i=0;i<nombre;i++) {
		neurones[i]=new ARTOutput(this,nombreE);
	}
	neurones[nombre]=0;
}

void ARTOutputLayer::UnReset()
{
	for (int i=0; neurones[i]; i++) {
		((ARTOutput*)neurones[i])->UnReset();
	}
}

void ARTOutputLayer::DesactiverNeurones()
{
	ARTCouche::DesactiverNeurones();
	neuroneRaisonnance = 0;
	iRaisonnance=-1;
}

void ARTOutputLayer::CalculerActivite()
{
	ARTCouche::CalculerActivite();

	float valeurRaisonnance = -0.00001;
	iRaisonnance = -1;
	neuroneRaisonnance = (ARTOutput*) 0;

	for (int i=0; neurones[i]; i++) {
		if ( neurones[i]->Activite() > valeurRaisonnance) {
			neuroneRaisonnance = (ARTOutput*) neurones[i];
			valeurRaisonnance = neurones[i]->Activite();
			iRaisonnance = i;
		}
	}

//	std::cout << " " << iRaisonnance;

}

void ARTOutputLayer::SortieBinaire()
{
	for (int i=0; neurones[i]; i++)
		neurones[i]->Sortie(0.0);

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

	for (int i=0; neurones[i]; i++){
		floatString.append(std::to_string(neurones[i]->Sortie()));
		floatString.append(" ");
		if (neurones[i]->Sortie()>0.9) {
			resultString += std::to_string(i);
			resultString += " ";
		}
	}
	std::cout << "=>\n";
	// std::cout << "OutputLayer " << floatString << "\n";
	std::cout << "Answer " << resultString << "\n";
}

ARTNeurone* ARTOutputLayer::BestMatch() {
	float bestResult = 0;
	int bestNeurone = -1;

	for (int i=0; neurones[i]; i++){
		float result = neurones[i]->Sortie();

		if (result>0.9) {
			if (result > bestResult) {
				bestResult = neurones[i]->Sortie();
				bestNeurone = i;
			}
		}
	}

	if (bestNeurone>=0) {
		return neurones[bestNeurone];
	} else {
		return 0;
	}
}

// **********************************************************************
// IMPLEMENTATION ARTNetwork
// **********************************************************************

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