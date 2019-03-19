#include "stdafx.h"
#include "Graphe.h"


Graphe::Graphe()
{
}


Graphe::~Graphe()
{
}

void Graphe::setSommets(std::vector<Sommet> sommets) {
sommets = sommets;
}

int Graphe::graphSize()
{
	return sommets.size();
}

Sommet Graphe::getSommet(int index) {
	return sommets[index];
}
