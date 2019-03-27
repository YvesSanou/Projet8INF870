#pragma once
#include "Graphe.h"

class GenerateurInstances
{
public:
	GenerateurInstances();
	~GenerateurInstances();
	Graphe testExemple(int sommets, int aretes);
	Graphe donnerExemple();
	Graphe donnerExemple2();
};

