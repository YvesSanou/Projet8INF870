#pragma once
#include "Graphe.h"

class GenerateurInstances
{
public:
	GenerateurInstances();
	~GenerateurInstances();
	Graphe randomExemple(int sommets, int aretes);
	Graphe exempleSolutionConnue(int tailleSolution, int sommetsMin, int aretesMin);
	Graphe donnerExemple();
	Graphe donnerExemple2();
	Graphe GenerateurInstances::exempleMatriceAdjacence(std::vector<std::vector<int>> matrice);
	void affichageMatriceAdjacence(Graphe g);
	void affichageAdjacenceVecteur(Graphe g);
};

