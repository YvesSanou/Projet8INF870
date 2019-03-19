#pragma once
#include <vector>
#include "Sommet.h"
class Graphe
{

private:
	std::vector<Sommet> sommets;
public:
	Graphe();
	~Graphe();
	Sommet Graphe::getSommet(int index);
	int Graphe::graphSize();
	void Graphe::setSommets(std::vector<Sommet> sommets);
};

