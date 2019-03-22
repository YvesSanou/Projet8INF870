#include "stdafx.h"
#include "AlgoExact.h"
#include "Sommet.h"
#include <iostream>
#include <algorithm>
#include <map>


AlgoExact::AlgoExact()
{

}


AlgoExact::~AlgoExact()
{
}

Solution AlgoExact::resoudreTrivial(Graphe graphe)
{
	Solution solutionFinale;
	Solution s;
	int n = graphe.getSommets().size();
	int nSub = 1 << n;
	for (int i = 0; i < nSub; i++)
	{
		//Generate a subset
		std::vector<Sommet*> subset;
		for (int k = 0; k < n; k++)
		{
			//if the k-th bit is set
			if ((1 << k) & i)
			{
				subset.push_back(graphe.getSommets()[k]);
			}
		}

		//Use the subset to construct a Solution
		s.setSequence(subset);
		//s.afficherSolution();

		//Test the solution
		if ( graphe.solutionValide(s) && (s.getSequence().size() < solutionFinale.getSequence().size() || solutionFinale.getSequence().size() == 0))
		{
			solutionFinale = s;
			//std::cout << "===========================" << std::endl;
			//std::cout << "Oh, une meilleure solution!" << std::endl;
			//solutionFinale.afficherSolution();
			//std::cout << "===========================" << std::endl;
		}
	}

	return solutionFinale;
}

Solution AlgoExact::resoudreReed(Graphe graphe)
{
	std::vector<Sommet*> listeSommets = graphe.getSommets();

	//Avoir l'ensemble des sommets avec 1 unique voisins
	//Avoir l'ensemble des sommets avec 2 voisins
	//Avoir l'ensemble des sommets avec 3 voisins ou plus
	std::vector<Sommet*> listeSommets1;
	std::vector<Sommet*> listeSommets2;
	std::vector<Sommet*> listeSommets3EtPlus;
	for(int i = 0; i < listeSommets.size(); i++)
	{
		if (listeSommets[i]->getVoisins().size() == 1)
		{
			listeSommets1.push_back(listeSommets[i]);
		}
		else if (listeSommets[i]->getVoisins().size() == 2)
		{
			listeSommets2.push_back(listeSommets[i]);
		}
		else
		{
			listeSommets3EtPlus.push_back(listeSommets[i]);
		}
	}
	
	return Solution();
}

Solution AlgoExact::resoudreGrandoni(Graphe graphe)
{
	std::vector<Sommet*> listeSommets = graphe.getSommets();

	//Transform into Minimum set cover problem
	for (int i =0; i < listeSommets.size(); i++)
	{
		listeSommets[i]->setSuperVoisins();
	}

	return Solution();
}

int MinimumSetCover(Graphe graphe)
{
	std::vector<Sommet*> listeSommets = graphe.getSommets();

	if (listeSommets.size() == 0)
	{
		return 0;
	}

	int index;
	//Si il existe un vector superVoisins inclu dans un autre, on ne le considère pas
	for (int i = 0; i < listeSommets.size(); i++)
	{
		//On récupère le superVoisin courant
		std::vector<int> superVoisinsCourant = listeSommets[i]->getSuperVoisins();
		//On vérifie s'il est inclus dans un autre
		for (int j = 0; j < listeSommets.size(); j++)
		{
			//On récupère le superVoisin2 courant
			std::vector<int> superVoisinsCourant2 = listeSommets[j]->getSuperVoisins();
			if (i != j)
			{
				std::vector<Sommet*> intersec;
				//std::set_intersection(superVoisinsCourant.begin(), superVoisinsCourant.end(), superVoisinsCourant2.begin(), superVoisinsCourant2.end(), std::back_inserter(intersec),[](Sommet* i, Sommet* j) { return (i->getId() < j->getId()); });
				// Si il existe un vector superVoisins inclu dans un autre, on ne le considère plus
				if (intersec.size() == superVoisinsCourant.size())
				{
					Graphe graphe2 = graphe;
					graphe2.deleteSommetFromIndex(i);
					MinimumSetCover(graphe2);
				}
			}
		}
	}

	//Construction d'une map de présence
	std::map<int, int> m;
	for(int i = 0; i < listeSommets.size(); i++)
	{
		m[listeSommets[i]->getId()] = 0;
	}

	for (int i = 0; i < listeSommets.size(); i++)
	{
		//Compter la présence de listeSommets[i]->getId() dans les supers voisins
		for (int j = 0; j < listeSommets.size(); j++)
		{
			if (std::find(
				listeSommets[j]->getSuperVoisins().begin(), 
				listeSommets[j]->getSuperVoisins().end(), 
				listeSommets[i]->getId()) 
				!= listeSommets[j]->getSuperVoisins().end())
			{
				m[listeSommets[i]->getId()]++;
			}
		}
	}

	//Y en at'il un qui n'apparait qu'une fois?
	for (int i = 0; i < listeSommets.size(); i++)
	{
		if (m[listeSommets[i]->getId()] == 1)
		{
			return 1 + MinimumSetCover(graphe);
		}
	}

	//Si l'on est capable de voir qu'un id se trouve dans un unique superVoisin




	return 0;
}
