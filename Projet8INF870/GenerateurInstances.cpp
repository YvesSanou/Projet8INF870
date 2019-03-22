#include "stdafx.h""
#include "Solution.h"
#include "Sommet.h"
#include "Graphe.h"
#include "GenerateurInstances.h"

GenerateurInstances::GenerateurInstances()
{
}

GenerateurInstances::~GenerateurInstances()
{
}

Graphe GenerateurInstances::donnerExemple()
{
	std::vector<Sommet*> sommets;
	// std::vector<Sommet> sommetsOpti;
	Graphe g = Graphe();
	// Solution s;

	std::vector<int> listeSommets = { 0,1,2,3,4,5,6,7,8,9 };
	// std::vector<int> listeSolOpti = { 0,4,8 };
	std::vector< std::vector<int> > voisins = { { 1,2,3 },{ 0, 6, 7 },{ 0, 4, 8 },
	{ 0, 5, 9 },{ 2, 5, 7 },{ 4, 6, 3 },{ 1, 5, 8 },
	{ 4, 1, 9 },{ 2, 6, 9 },{ 7, 8, 3 } };

	for (int i = 0; i < listeSommets.size(); i++) {
		Sommet* pointeurSommet = new Sommet(listeSommets[i]);
		sommets.push_back(pointeurSommet);
	}
	for (int i = 0; i < voisins.size(); i++) {
		for (int j = 0; j < voisins[i].size(); j++) {
			sommets.at(i)->addVoisin(voisins[i][j]);
		}
	}
	/* for (int i = 0; i < listeSolOpti.size(); i++) {
		sommetsOpti.push_back(sommets.at(listeSolOpti[i]));
	} */

	g.setSommets(sommets);

	return g;
}
