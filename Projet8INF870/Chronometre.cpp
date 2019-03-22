#include "stdafx.h"
#include "Chronometre.h"


Chronometre::Chronometre()
{
}


Chronometre::~Chronometre()
{
}

void Chronometre::start()
{
	time(&debut);
}

void Chronometre::stop()
{
	time(&fin);

	tempsEcoule = difftime(fin, debut);
}

void Chronometre::afficherTempsEcoule()
{
	std::cout << "Temps ecoule: " << tempsEcoule << "secondes\n";
}
