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

Graphe GenerateurInstances::randomExemple(int nombreSommets, int nombreAretes) {
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

		//std::cout << x << " " << y << std::endl;
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

		//std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);
	}

	// Affichage matrice d'adjacence (utiliser http://graphonline.ru/en/create_graph_by_matrix)
	/*
	for (int i = 0; i < nombreSommets; i++)
	{
		std::vector<int> voisinsi = sommets.at(i)->getVoisins();
		for (int j = 0; j < nombreSommets; j++)
		{
			if (std::find(voisinsi.begin(), voisinsi.end(), j) != voisinsi.end())
				std::cout << 1;
			else
				std::cout << 0;
			std::cout << " ";
		}
		std::cout << std::endl;
	}*/

	g.setSommets(sommets);
	return g;
}

Graphe GenerateurInstances::exempleSolutionConnue(int tailleSolution, int sommetsMin, int aretesMin) {
	std::vector<Sommet *> sommets;
	std::vector<int> solution;
	std::vector<std::vector<int>> sommetsAssocies(tailleSolution, std::vector<int>(0));
	std::vector<int> sommetsUniques;
	int nombreSommets;
	Graphe g = Graphe();

	srand(time(NULL));

	if (sommetsMin < 2 * tailleSolution)
		nombreSommets = 2 * tailleSolution;
	else
		nombreSommets = sommetsMin;

	// création sommets
	for (int i = 0; i < nombreSommets; i++) {
		sommets.push_back(new Sommet(i));
	}

	// génération sommets aléatoires
	for (int i = 0; i < tailleSolution; i++) {
		int value = rand() % nombreSommets;
		if (std::find(solution.begin(), solution.end(), value) == solution.end())
		{
			solution.push_back(value);
			sommetsAssocies.at(i).push_back(value);
		}
		else
			i--;
	}

	// génération sommets uniques (permettant aux sommets solutions d'être optimaux)
	for (int i = 0; i < tailleSolution; i++) {
		int value = rand() % nombreSommets;
		if (std::find(solution.begin(), solution.end(), value) == solution.end() && std::find(sommetsUniques.begin(), sommetsUniques.end(), value) == sommetsUniques.end())
			sommetsUniques.push_back(value);
		else
			i--;
	}

	// ajout d'un sommet voisin spécifique à chaque sommet de la solution optimale
	for (int i = 0; i < tailleSolution; i++)
	{
		//std::cout << solution[i] << " " << sommetsUniques[i] << std::endl;
		sommets.at(solution[i])->addVoisin(sommetsUniques[i]);
		sommets.at(sommetsUniques[i])->addVoisin(solution[i]);
	}

	// Pour attacher chaque point à au moins un sommet de la solution optimale
	for (int j = 0; j < nombreSommets; j++)
	{
		if (std::find(solution.begin(), solution.end(), j) != solution.end() || std::find(sommetsUniques.begin(), sommetsUniques.end(), j) != sommetsUniques.end())
			continue;
		int x, y, k;
		k = rand() % tailleSolution;
		x = j;
		y = solution.at(k);

		//std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);

		sommetsAssocies.at(k).push_back(j);
	}

	// On a un groupe de sommets pour chaque sommet de la solution optimale
	// Il faut relier ces groupes pour avoir un graphe correct

	for (int i = 0; i < tailleSolution; i++)
	{
		int k;
		do {
			k = rand() % tailleSolution;
		} while (k == i);
		int x = sommetsAssocies.at(i).at(rand() % sommetsAssocies.at(i).size());
		int y = sommetsAssocies.at(k).at(rand() % sommetsAssocies.at(k).size());

		//std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);
	}

	for (int j = nombreSommets + tailleSolution; j < aretesMin; j++)
	{
		std::vector<int> voisins;
		int x, y;
		do {
			x = rand() % nombreSommets;
			do {
				y = rand() % nombreSommets;
			} while ((x == y));

			voisins = sommets.at(x)->getVoisins();
		} while (std::find(voisins.begin(), voisins.end(), y) != voisins.end() || std::find(sommetsUniques.begin(), sommetsUniques.end(), x) != sommetsUniques.end() ||
			std::find(sommetsUniques.begin(), sommetsUniques.end(), y) != sommetsUniques.end());

		//std::cout << x << " " << y << std::endl;
		sommets.at(x)->addVoisin(y);
		sommets.at(y)->addVoisin(x);
	}

	// Affichage matrice d'adjacence (utiliser http://graphonline.ru/en/create_graph_by_matrix)
	/*
	for (int i = 0; i < nombreSommets; i++)
	{
		std::vector<int> voisinsi = sommets.at(i)->getVoisins();
		for (int j = 0; j < nombreSommets; j++)
		{
			if (std::find(voisinsi.begin(), voisinsi.end(), j) != voisinsi.end())
				std::cout << 1;
			else
				std::cout << 0;
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < tailleSolution; i++)
		std::cout << solution.at(i) << " ";
	std::cout << std::endl;
	for (int i = 0; i < tailleSolution; i++)
		std::cout << sommetsUniques.at(i) << " ";
	std::cout << std::endl;*/

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

Graphe GenerateurInstances::donnerExemple2()
{
	std::vector<Sommet*> sommets;
	// std::vector<Sommet> sommetsOpti;
	Graphe g = Graphe();
	// Solution s;

	std::vector<int> listeSommets = { 0,1,2,3,4,5};
	// std::vector<int> listeSolOpti = { 0,4,8 };
	std::vector< std::vector<int> > voisins = { { 5,3,4 },{ 5, 3, 4 },{ 5, 4 },
	{ 0, 1, 4, 5 },{ 0, 3, 2, 1 },{ 0, 3, 2, 1} };

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

