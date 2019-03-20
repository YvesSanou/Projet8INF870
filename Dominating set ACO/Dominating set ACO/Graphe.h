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
	std::vector<Sommet> Graphe::getSommets();
	Sommet Graphe::getSommetFromId(int id);
	int Graphe::graphSize();
	void Graphe::setSommets(std::vector<Sommet> sommets);
};

