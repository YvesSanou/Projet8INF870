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

Sommet Graphe::getSommetFromId(int id)
{
	Sommet sommetCherche;

	for (int i =0; i < sommets.size(); i++)
	{
		if (sommets[i].getId == id)
		{
			sommetCherche = sommets[i];
		}
	}

	return sommetCherche;
}
