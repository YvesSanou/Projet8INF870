#include "stdafx.h"
#include "Chronometre.h"


Chronometre::Chronometre()
{
}


Chronometre::~Chronometre()
{
}

void Chronometre::start(std::string message)
{
	std::cout << message << std::endl;
	time(&debut);
}

void Chronometre::stop(std::string message)
{
	std::cout << message << std::endl;
	time(&fin);
	tempsEcoule = difftime(fin, debut);
}

void Chronometre::afficherTempsEcoule()
{
	std::cout << "Temps ecoule: " << tempsEcoule << "secondes\n";
}

int Chronometre::getTempsEcoule()
{
	return tempsEcoule;
}
