#include <iostream>

#include "shell.hpp"

int Message( const char *sMessage )
{
	std::cout << "Message : " << sMessage << "\n";
	return 0;
}

int Prompt( const char *sMessage )
{
	std::cout << "Prompt : " << sMessage << "\n";
	char c;
	std::cin >> c;
	return 0;
}

int Erreur( const char *sMessage )
{
	std::cout << "Erreur : " << sMessage << "\n";
	char c;
	std::cin >> c;
	return 0;
}

std::string Attendre(const char* s)
{
	std::string texte;
	std::cout << "\n" << s << "\n";
	std::getline(std::cin, texte);
	return texte;
}
