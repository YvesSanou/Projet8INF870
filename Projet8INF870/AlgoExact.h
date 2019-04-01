#pragma once
#include "Sommet.h"
#include "Graphe.h"

class AlgoExact
{
	private:
		Graphe supprimerSommetsSuperVoisins(Graphe graphe, std::vector<int> sommetsASupprimer);
		Solution fusionnerSolutions(Solution s1, Solution s2);
		Solution MinimumSetCover(Graphe graphe);

	public:
		AlgoExact();
		~AlgoExact();
		Solution resoudreTrivial(Graphe graphe);
		Solution resoudreGrandoni(Graphe graphe);
};

