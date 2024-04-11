#define K 1.0
#define _ 0.0

#include <string.h>

#define NEXEMPLE	20
#define NENTREES	25
#define NSORTIES	12

float lettre_A[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,K,
				K,K,K,K,K,
				K,_,_,_,K,
				K,_,_,_,K };

float lettre_B[NENTREES] ={ 	K,K,K,K,_,
				K,_,_,_,K,
				K,K,K,K,_,
				K,_,_,_,K,
				K,K,K,K,_ };

float lettre_C[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,_,
				K,_,_,_,_,
				K,_,_,_,_,
				K,K,K,K,K };

float lettre_D[NENTREES] ={ 	K,K,K,K,_,
				K,_,_,_,K,
				K,_,_,_,K,
				K,_,_,_,K,
				K,K,K,K,_ };

float lettre_E[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,_,
				K,K,K,K,K,
				K,_,_,_,_,
				K,K,K,K,K };

float lettre_F[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,_,
				K,K,K,K,K,
				K,_,_,_,_,
				K,_,_,_,_ };

float lettre_G[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,_,
				K,_,K,K,K,
				K,_,_,_,K,
				K,K,K,K,K };

float lettre_H[NENTREES] ={ 	K,_,_,_,K,
				K,_,_,_,K,
				K,K,K,K,K,
				K,_,_,_,K,
				K,_,_,_,K };

float lettre_I[NENTREES] ={ 	K,K,K,K,K,
				_,_,K,_,_,
				_,_,K,_,_,
				_,_,K,_,_,
				K,K,K,K,K };

float lettre_J[NENTREES] ={ 	K,K,K,K,K,
				_,_,K,_,_,
				_,_,K,_,_,
				_,_,K,_,_,
				K,K,K,_,_ };

float lettre_K[NENTREES] ={ 	K,_,_,_,K,
				K,_,_,K,_,
				K,K,K,_,_,
				K,_,_,K,_,
				K,_,_,_,K };

float lettre_L[NENTREES] ={ 	K,_,_,_,_,
				K,_,_,_,_,
				K,_,_,_,_,
				K,_,_,_,_,
				K,K,K,K,K };

float lettre_M[NENTREES] ={ 	K,_,_,_,K,
				K,K,_,K,K,
				K,_,K,_,K,
				K,_,_,_,K,
				K,_,_,_,K };

float lettre_N[NENTREES] ={ 	K,_,_,_,K,
				K,K,_,_,K,
				K,_,K,_,K,
				K,_,_,K,K,
				K,_,_,_,K };

float lettre_O[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,K,
				K,_,_,_,K,
				K,_,_,_,K,
				K,K,K,K,K };

float lettre_P[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,K,
				K,K,K,K,K,
				K,_,_,_,_,
				K,_,_,_,_ };

float lettre_Q[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,K,
				K,_,K,_,K,
				K,_,_,K,K,
				K,K,K,K,K };

float lettre_R[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,K,
				K,K,K,K,K,
				K,_,_,K,_,
				K,_,_,_,K };

float lettre_S[NENTREES] ={ 	K,K,K,K,K,
				K,_,_,_,_,
				K,K,K,K,K,
				_,_,_,_,K,
				K,K,K,K,K };

float lettre_T[NENTREES] ={ 	K,K,K,K,K,
				_,_,K,_,_,
				_,_,K,_,_,
				_,_,K,_,_,
				_,_,K,_,_ };

float** getPattern(char* buffer,int& ne,int &ni)
{
	ne = NEXEMPLE;
	ni = NENTREES;
	float** figure = (float**) calloc(NEXEMPLE+1,sizeof(float*));
	figure[0] = lettre_A;
	figure[1] = lettre_B;
	figure[2] = lettre_C;
	figure[3] = lettre_D;
	figure[4] = lettre_E;
	figure[5] = lettre_F;
	figure[6] = lettre_G;
	figure[7] = lettre_H;
	figure[8] = lettre_I;
	figure[9]= lettre_J;
	figure[10]= lettre_K;
	figure[11]= lettre_L;
	figure[12]= lettre_M;
	figure[13]= lettre_N;
	figure[14]= lettre_O;
	figure[15]= lettre_P;
	figure[16]= lettre_Q;
	figure[17]= lettre_R;
	figure[18]= lettre_S;
	figure[19]= lettre_T;
	figure[NEXEMPLE]=0;

	strcpy(buffer,"ABCDEFGHIJKLMNOPQRST");
	return figure;
}

