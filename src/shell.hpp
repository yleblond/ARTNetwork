#ifndef HEADER_DEBUG
#define HEADER_DEBUG

#include <string>

int Prompt( const char *sMessage );
int Message( const char *sMessage );
int Erreur( const char *sMessage );
std::string Attendre(const char* s);

#endif


