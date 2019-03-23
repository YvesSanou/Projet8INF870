#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "Solution.h"
#include "Sommet.h"
#include "Graphe.h"
#include "GenerateurInstances.h"
#include <iostream>

GenerateurInstances::GenerateurInstances()
{
}

GenerateurInstances::~GenerateurInstances()
{
}

Graphe GenerateurInstances::testExemple(int nombreSommets, int nombreAretes) {
	std::vector<Sommet *> sommets;
	Graphe g = Graphe();

	srand(time(NULL));

	// création sommets
	for (int i = 0; i < nombreSommets; i++) {
		sommets.push_back(new Sommet(i));
	}

	// ajout d'un sommet voisin spécifique à chaque sommet de la solution optimale
	/*for (int j = 0; j < nombreSommetsSolOpti; j++)
	{
		std::cout << j << " " << j + nombreSommetsSolOpti << std::endl;
		sommets.at(j)->addVoisin(j + nombreSommetsSolOpti);
		sommets.at(j + nombreSommetsSolOpti)->addVoisin(j);
	}*/

	// Pour être sûr que tous les sommets soient connectés à au moins un autre
	for (int j = 0; j < nombreSommets; j++)
	{
		int x, y;
		x = j;
		do {
			y = rand() % nombreSommets;
		} while ((x == y));

		std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);
	}

	for (int j = nombreSommets; j < nombreAretes; j++)
	{
		std::vector<int> voisins;
		int x, y;
		do {
			x = rand() % nombreSommets;
			do {
				y = rand() % nombreSommets;
			} while ((x == y));

			voisins = sommets.at(x)->getVoisins();
		} while (std::find(voisins.begin(), voisins.end(), y) != voisins.end());

		std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);
	}

	g.setSommets(sommets);
	return g;
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
