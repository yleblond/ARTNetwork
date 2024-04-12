#ifndef HEADER_PROCESS_SETTINGS
#define HEADER_PROCESS_SETTINGS

class ProcessSettings {

	// learning process
	public:
		int LEARNING_LOOPS	= 1;
		int LEARNING_ITERATION	= 20;
		int LEARNING_MAXITEMS	= -1;

	// querying process
	public:
		int QUERY_ITERATION	= 10;
		int QUERY_MAXITEMS	= -1;

};

#endif
