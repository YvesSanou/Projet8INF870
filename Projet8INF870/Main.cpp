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
	ACO aco;
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
	Graphe graphe2 = generateur.exempleSolutionConnue(100, 150, 600);
	//Graphe graphe2 = generateur.donnerExemple2();

	/*
	chrono.start("\n=========================\nDEBUT chronometrage methode TRIVIALE");
	Solution solution2 = algoExact.resoudreTrivial(graphe2);
	chrono.stop("FIN chronometrage methode TRIVIALE\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << std::endl;
	solution2.afficherSolution();*/
	std::vector<int> timesInSecondes;
	std::vector<int> ecarts;
	for (int i = 100; i < 3000; i += 100)
	{
		Graphe graphe2 = generateur.exempleSolutionConnue(i / 2, i, 2*i);
		std::cout << "Taille graphe: " << graphe2.getSommets().size() << " sommet(s)" << std::endl;

		chrono.start("\n=========================\nDEBUT chronometrage methode ACO");
		Solution solution3 = aco.run(graphe2);
		chrono.stop("FIN chronometrage methode ACO\n=========================\n");
		chrono.afficherTempsEcoule();
		int ecart = solution3.getSequence().size() - (i / 2);
		std::cout << "i:" << i << std::endl;
		std::cout << "Solution finale:" << graphe2.solutionValide(solution3) << std::endl;
		std::cout << "Taille solution optimale:" << solution3.getSequence().size() << std::endl;
		std::cout << "Ecart solution optimale:" << ecart << std::endl;
		solution3.afficherSolution();
		timesInSecondes.push_back(chrono.getTempsEcoule());
		ecarts.push_back(ecart);


		std::cout << "Temps ecoules en secondes\n{";
		for (int j = 0; j < timesInSecondes.size(); j++)
		{
			std::cout << timesInSecondes[j] << ", ";
		}
		std::cout << "}\n";

		std::cout << "Ecarts\n{";
		for (int j = 0; j < ecarts.size(); j++)
		{
			std::cout << ecarts[j] << ", ";
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

