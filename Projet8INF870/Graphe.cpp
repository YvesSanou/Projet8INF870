#include "stdafx.h"
#include "Graphe.h"
#include <algorithm>
#include <iostream>
#include <fstream>


Graphe::Graphe()
{
}


Graphe::~Graphe()
{
}

void Graphe::setSommets(std::vector<Sommet*> value) 
{
	sommets = value;
}

bool Graphe::solutionValide(Solution solution)
{

	if (solution.getSequence().size() == 0)
	{
		return false;
	}

	std::vector<Sommet*> listeSommetsSolution = solution.getSequence();

	std::vector<Sommet*> sommetsCouverts;

	for (int i = 0; i < listeSommetsSolution.size(); i++) 
	{
		//On met le sommet en question
		sommetsCouverts.push_back(listeSommetsSolution[i]);

		//on met ces voisins
		for (int j = 0; j < listeSommetsSolution[i]->getVoisins().size(); j++)
		{
			sommetsCouverts.push_back(Graphe::getSommetFromId(listeSommetsSolution[i]->getVoisins()[j]));
		}
	}

	//On enlève les doublons
	sommetsCouverts.erase(std::unique(sommetsCouverts.begin(), sommetsCouverts.end()), sommetsCouverts.end());

	//On compare "sommetsCouverts" avec les sommets du graphe "sommetsGraphe"
	std::vector<Sommet*> sommetsGraphe = Graphe::sommets;

	//Pour cela, on commence par les trier
	std::sort(sommetsGraphe.begin(), sommetsGraphe.end(), [](Sommet* i, Sommet* j) { return (i->getId() < j->getId()); });
	std::sort(sommetsCouverts.begin(), sommetsCouverts.end(), [](Sommet* i, Sommet* j) { return (i->getId() < j->getId()); });

	//Puis on vérifie l'intersection
	std::vector<Sommet*> intersec;
	std::set_intersection(sommetsGraphe.begin(), sommetsGraphe.end(), sommetsCouverts.begin(), sommetsCouverts.end(), std::back_inserter(intersec), 
		[](Sommet* i, Sommet* j) { return (i->getId() < j->getId()); });

	return intersec.size() == sommetsGraphe.size();
}

void Graphe::afficherSommets(std::vector<Sommet*> sommets)
{
	std::cout << "{" << std::endl;
	for (int i = 0; i < sommets.size(); i++)
	{
		std::cout << sommets[i]->getId()+ ", ";
	}
	std::cout << "}" << std::endl;
}

int Graphe::graphSize()
{
	return sommets.size();
}

std::vector<Sommet*> Graphe::getSommets() {
	return sommets;
}

Sommet* Graphe::getSommet(int index) {
	return sommets[index];
}

Sommet* Graphe::getSommetFromId(int id)
{
	for (int i =0; i < sommets.size(); i++)
	{
		if (sommets[i]->getId() == id)
		{
			return sommets[i];
		}
	}

	return nullptr;
}

void Graphe::deleteSommetFromIndex(int index)
{
	sommets.erase(sommets.begin() + index);
}

void Graphe::deleteSommetFromId(int id)
{
	int index;
	for (int i = 0; i < sommets.size(); i++)
	{
		if (id == sommets[i]->getId())
		{
			index = i;
		}
	}
	sommets.erase(sommets.begin() + index);
}
