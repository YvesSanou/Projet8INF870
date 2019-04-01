// Dominating set ACO.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "ACO.h"
#include "AlgoExact.h"
#include "Chronometre.h"
#include "GenerateurInstances.h"
#include <vector>
#include <iostream>


int main()
{
	AlgoExact algoExact;
	Chronometre chrono;
	/*

	chrono.start();
	Solution solution = algoExact.resoudreTrivial(graphe);
	chrono.stop();
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << std::endl;
	solution.afficherSolution();
	*/

	GenerateurInstances generateur;

	//std::vector<std::vector<int>> mat = {{0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},{1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0},{1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},{1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},{0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}};
	//Graphe graphe2 = generateur.exempleMatriceAdjacence(mat);
  
	std::vector<int> timesInSecondes;
	for (int i = 1; i < 2000; i += 100)
	{
		Graphe graphe2 = generateur.exempleSolutionConnue(i / 2, i, 2*i);
		std::cout << "Taille graphe: " << graphe2.getSommets().size() << " sommet(s)" << std::endl;

		chrono.start("\n=========================\nDEBUT chronometrage methode GRANDONI");
		Solution solution3 = algoExact.resoudreGrandoni(graphe2);
		chrono.stop("FIN chronometrage methode GRANDONI\n=========================\n");
		chrono.afficherTempsEcoule();
		std::cout << "Solution finale:" << graphe2.solutionValide(solution3) << std::endl;
		solution3.afficherSolution();
		timesInSecondes.push_back(chrono.getTempsEcoule());

		std::cout << "Temps ecoules en secondes\n{";
		for (int j = 0; j < timesInSecondes.size(); j++)
		{
			std::cout << timesInSecondes[j] << ", ";
		}
		std::cout << "}\n";
	}
	
	
	/*
	chrono.start("\n=========================\nDEBUT chronometrage methode GRANDONI");
	Solution solution3 = algoExact.resoudreGrandoni(graphe2);
	chrono.stop("FIN chronometrage methode GRANDONI\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << graphe2.solutionValide(solution3) << std::endl;
	solution3.afficherSolution();*/

	/*
	std::cout << "Ant Colony System" << std::endl;
	ACO algo;
	

	chrono.start("\n=========================\nDEBUT chronometrage methode ACO");
	Solution solution4 = algo.run(graphe2);
	chrono.stop("FIN chronometrage methode ACO\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << graphe2.solutionValide(solution4) << std::endl;
	solution4.afficherSolution();*/

	return 0;
}

