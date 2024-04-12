#ifndef HEADER_ART_SETTINGS
#define HEADER_ART_SETTINGS

class ARTSettings {
	// network parameters
	public:
		float I_PERSISTANCE =		0.0;
		float I_RENFORCEMENT =		1.9;
		float  I_INHIBATION =		2.1;
		float  I_AUTOINHIBATION =	0.0;
		float  I_VIGILANCE =		0.97; // 0.7 // 0.97
		float  I_PLASTICITE 	=	0.035;

		float  O_PERSISTANCE =		0.0;
		float  O_RENFORCEMENT =		1.6;
		float  O_INHIBATION 	=	2.2;
		float  O_AUTOINHIBATION =	0.0;
		float  O_CONTRAINTE_PLASTICITE = 1.4;

		float  N_ITERATIONS	=	25;
		float  N_REACTIVITE	=	0.1;

	// output grid
	public:
		int		nOutputs = 10;

	// weight display sensibility
	public:
		float WEIGHT_DISPLAY_THREESHOLD	= 0.005;
};

#endif
