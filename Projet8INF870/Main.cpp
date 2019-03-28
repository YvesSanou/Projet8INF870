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

	//Exemple graphe
	Sommet s1(1);
	s1.addVoisin(6);
	Sommet s2(2);
	s2.addVoisin(6);
	s2.addVoisin(7);
	Sommet s3(3);
	s3.addVoisin(6);
	Sommet s4(4);
	s4.addVoisin(6);
	Sommet s5(5);
	s5.addVoisin(6);
	Sommet s6(6);
	s6.addVoisin(1);
	s6.addVoisin(2);
	s6.addVoisin(3);
	s6.addVoisin(4);
	s6.addVoisin(5);
	Sommet s7(7);
	s7.addVoisin(2);

	std::vector<Sommet*> listeSommets;
	listeSommets.push_back(&s1);
	listeSommets.push_back(&s2);
	listeSommets.push_back(&s3);
	listeSommets.push_back(&s4);
	listeSommets.push_back(&s5);
	listeSommets.push_back(&s6);
	listeSommets.push_back(&s7);

	Graphe graphe;
	graphe.setSommets(listeSommets);

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
	Graphe graphe2 = generateur.exempleSolutionConnue(50, 60, 600);

	/*
	chrono.start("\n=========================\nDEBUT chronometrage methode TRIVIALE");
	Solution solution2 = algoExact.resoudreTrivial(graphe2);
	chrono.stop("FIN chronometrage methode TRIVIALE\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << std::endl;
	solution2.afficherSolution();*/
	

	chrono.start("\n=========================\nDEBUT chronometrage methode GRANDONI");
	Solution solution3 = algoExact.resoudreGrandoni(graphe2);
	chrono.stop("FIN chronometrage methode GRANDONI\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << graphe2.solutionValide(solution3) << std::endl;
	solution3.afficherSolution();

	
	std::cout << "Ant Colony System" << std::endl;
	ACO algo;
	

	chrono.start("\n=========================\nDEBUT chronometrage methode ACO");
	Solution solution4 = algo.run(graphe2);
	chrono.stop("FIN chronometrage methode ACO\n=========================\n");
	chrono.afficherTempsEcoule();
	std::cout << "Solution finale:" << graphe2.solutionValide(solution4) << std::endl;
	solution4.afficherSolution();

	return 0;
}

