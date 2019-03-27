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
		listeSommets[i]->initSuperVoisins();
	}

	return MinimumSetCover(graphe);
}

Graphe AlgoExact::supprimerSommetsSuperVoisins(Graphe graphe, std::vector<int> sommetsASupprimer)
{
	// Pour chaque sommet à supprimeryhgt
	int test = 0;

	//On cherche les supersVoisins contenant ce sommet
	std::vector<Sommet*> listeSommets = graphe.getSommets();

	//On fait une copie de mes sommets
	std::vector<Sommet*> copyListeSommets;
	for (int i = 0; i < listeSommets.size(); i++)
	{
		Sommet* copySommet= new Sommet();
		*copySommet = *listeSommets[i];
		copyListeSommets.push_back(copySommet);
	}

	for (int i = 0; i < sommetsASupprimer.size(); i++)
	{
		for (int j = 0; j < copyListeSommets.size(); j++)
		{
			//si listeSommets[j]->getSuperVoisins() contient sommetsASupprimer[i]->getId()
			std::vector<int> superVoisins = copyListeSommets[j]->getSuperVoisins();

			//Ici on fait disparaitre le voisin des superVoisins
			superVoisins.erase(std::remove_if(superVoisins.begin(), superVoisins.end(), [&](int unSuperVoisin)
			{
				return unSuperVoisin == sommetsASupprimer[i];
			}), superVoisins.end());

			//Update
			copyListeSommets[j]->setSuperVoisins(superVoisins);

		}
		graphe.setSommets(copyListeSommets);
	}
	


	//Si un sommet se retrouve avec un superVoisins vide, on supprime le sommet
	std::vector<Sommet*> nouvelleListeSommets = graphe.getSommets();
	std::vector<int> idsToDelete;
	for (int i = 0; i < nouvelleListeSommets.size(); i++)
	{
		if (nouvelleListeSommets[i]->getSuperVoisins().size() == 0)
		{
			idsToDelete.push_back(nouvelleListeSommets[i]->getId());
		}
	}
	for (int i = 0; i < idsToDelete.size(); i++)
	{
		graphe.deleteSommetFromId(idsToDelete[i]);
	}

	return graphe;
}

Solution AlgoExact::fusionnerSolutions(Solution s1, Solution s2)
{
	std::vector<Sommet*> sommetsS;

	std::vector<Sommet*> sommetsS1 = s1.getSequence();
	std::vector<Sommet*> sommetsS2 = s2.getSequence();
	
	//On ajoute les sommets des 2 solutions
	for (int i =0; i < sommetsS1.size(); i++)
	{
		sommetsS.push_back(sommetsS1[i]);
	}
	for (int i = 0; i < sommetsS2.size(); i++)
	{
		sommetsS.push_back(sommetsS2[i]);
	}

	Solution s;
	s.setSequence(sommetsS);

	return s;
}

Solution AlgoExact::MinimumSetCover(Graphe graphe)
{
	std::vector<Sommet*> listeSommets = graphe.getSommets();

	//S'il n'y plus de sommets, on retourne une solution vide
	if (listeSommets.size() == 0)
	{
		Solution s;
		return s;
	}

	int index;
	//S'il existe un vector superVoisins inclu dans un autre, on ne le considère pas
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
				//On trouve l'intersection des 2 ensembles

				//d'abord, on trie
				std::sort(superVoisinsCourant.begin(), superVoisinsCourant.end());
				std::sort(superVoisinsCourant2.begin(), superVoisinsCourant2.end());

				std::vector<int> intersec;
				std::set_intersection(superVoisinsCourant.begin(), superVoisinsCourant.end(), superVoisinsCourant2.begin(), superVoisinsCourant2.end(), std::back_inserter(intersec));
				// Si il existe un vector superVoisins inclu dans un autre, on ne le considère plus
				if (intersec.size() == superVoisinsCourant.size())
				{
					Graphe graphe2 = graphe;
					graphe2.deleteSommetFromIndex(i);
					return MinimumSetCover(graphe2);
				}
			}
		}
	}

	//Y en at'il un qui n'apparait qu'une fois?
	//Construction d'une map de présence
	std::map<int, int> m;
		//Compter la présence de listeSommets[i]->getId() dans les supers voisins
	for (int i = 0; i < listeSommets.size(); i++)
	{
		std::vector<int> superVoisins = listeSommets[i]->getSuperVoisins();

		for (int j = 0; j < superVoisins.size(); j++)
		{
			if (m.find(superVoisins[j]) == m.end())
			{
				m[superVoisins[j]] = 1;
			}
			else
			{
				m[superVoisins[j]]++;
			}
		}

	}
	
	//Y en at'il vraiment un qui n'apparait qu'une fois?
	for (std::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		if (it->second == 1)
		{
			//Ce sommet est à ajouter à la solution partielle
			//Et à supprimer pour l'appel récursif
			
			//Trouvons le premier sommet où se trouve it->first
			for (int k = 0; k < listeSommets.size(); k++)
			{
				std::vector<int> superVoisins = listeSommets[k]->getSuperVoisins();
				if (std::find(superVoisins.begin(), superVoisins.end(), it->first) != superVoisins.end())
				{
					Solution sTemp;
					std::vector<Sommet*> sommetsTemp;
					sommetsTemp.push_back(listeSommets[k]);
					sTemp.setSequence(sommetsTemp);
					//On fusionne les solutions
					return fusionnerSolutions(sTemp, MinimumSetCover(supprimerSommetsSuperVoisins(graphe, listeSommets[k]->getSuperVoisins())));

				}
			}
		}
	}

	//Trouver le sommet dont le superVoisin dont la cardinalité est maximale
	Sommet* sMax = listeSommets[0];
	int indexSMax = 0;
	for (int i = 1; i < listeSommets.size(); i++)
	{
		if (sMax->getSuperVoisins().size() < listeSommets[i]->getSuperVoisins().size())
		{
			sMax = listeSommets[i];
			indexSMax = i;
		}
	}

	//min (MSC(S/S), MSC(del(S,S)))
	Graphe grapheTemp = graphe;
	grapheTemp.deleteSommetFromIndex(indexSMax);

	//On calcule les solutions
	Solution s1 = MinimumSetCover(grapheTemp);

	Solution sTemp2;
	std::vector<Sommet*> sommetsTemp2;
	sommetsTemp2.push_back(sMax);
	sTemp2.setSequence(sommetsTemp2);
	Solution s2 = fusionnerSolutions(sTemp2, MinimumSetCover(supprimerSommetsSuperVoisins(graphe, sMax->getSuperVoisins())));

	//On prend la plus petite des deux
	if (s1.getSequence().size() < s2.getSequence().size())
	{
		return s1;
	}
	else
	{
		return s2;
	}
}
