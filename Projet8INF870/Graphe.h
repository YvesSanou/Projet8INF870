#pragma once
#include <vector>
#include "Sommet.h"
#include "Solution.h"
class Solution;

class Graphe
{

private:
	std::vector<Sommet*> sommets;
public:
	Graphe();
	~Graphe();
	Sommet* Graphe::getSommet(int index);
	std::vector<Sommet*> Graphe::getSommets();
	Sommet* Graphe::getSommetFromId(int id);
	void Graphe::deleteSommetFromIndex(int index);
	int Graphe::graphSize();
	void Graphe::setSommets(std::vector<Sommet*> sommets);
	bool solutionValide(Solution solution);
	void afficherSommets(std::vector<Sommet*> sommets);
};

