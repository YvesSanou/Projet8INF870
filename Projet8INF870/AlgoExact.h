#pragma once
#include "Sommet.h"
#include "Graphe.h"

class AlgoExact
{
	private:
		Graphe supprimerSommetsSuperVoisins(Graphe graphe, std::vector<Sommet*> sommetsASupprimer);
		Solution fusionnerSolutions(Solution s1, Solution s2);
		Solution MinimumSetCover(Graphe graphe);

	public:
		AlgoExact();
		~AlgoExact();
		Solution resoudreTrivial(Graphe graphe);
		Solution resoudreReed(Graphe graphe);
		Solution resoudreGrandoni(Graphe graphe);
};

