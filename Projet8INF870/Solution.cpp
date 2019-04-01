#include "stdafx.h"
#include "Solution.h"
#include <iostream>


Solution::Solution()
{
}


Solution::~Solution()
{
}

void Solution::initialize(std::vector<Sommet*> sommets) {
	grapheSize = sommets.size();
	sommetsNonSelectionnes = sommets;
	sommetsNonCouverts = sommets;
	sommetCourant = sommets[rand() % sommets.size()];
}

void Solution::nextStep(Graphe graphe, double evap, double t0, double q, int alpha) {
	double random = rand() % RAND_MAX;
	Sommet* selection;	
	std::vector<Sommet*> voisins = voisinsValides((*sommetCourant).getPVoisins());
	if (voisins.size() == 0)
	{
		int i = -1;
		do {
			i++;
			sommetCourant = sommetsNonSelectionnes[i];
			voisins = voisinsValides((*sommetCourant).getPVoisins());
		} while (voisins.size() == 0);
	}
	voisins.push_back(sommetCourant);
	//Exploitation
	if (random > q) {
		//selection = sommetsNonSelectionnes[0]
		selection = voisins[0];
		int vis = visibilite(selection, graphe);
		double value = selection->getTrace() * (pow(vis, alpha));
		//for (int i = 1; i < sommetsNonSelectionnes.size(); i++) {
		for (int i = 1; i < voisins.size(); i++) {
			//Sommet* current = sommetsNonSelectionnes[i];
			Sommet* current = voisins[i];
			vis = visibilite(current, graphe);
			double temp = current->getTrace() * (pow(vis, alpha));
			if (temp > value) {
				value = temp;
				selection = current;
			}
		}
	}

	//Exploration
	else {
		std::vector<double> probs = std::vector<double>();
		double probSum = 0;
		//for (int i = 0; i < sommetsNonSelectionnes.size(); i++) {
		for (int i = 0; i < voisins.size(); i++) {
			Sommet* sommet = voisins[i];
			int vis = visibilite(sommet, graphe);
			double trace = sommet->getTrace();
			double value = trace * pow(vis, alpha);
			probs.push_back(value);
			probSum += value;
		}
		
		for (int i = 0; i < probs.size(); i++) {
			double prob = probs[i];
			prob = prob / probSum;
		}
		int index = Solution::selection(probs);
		selection =voisins[index];
		int a = 0;
	}
	addSommet(selection, graphe, evap, t0);
}

void Solution::addSommet(Sommet* sommet,Graphe graphe, double evap, double t0) {
	sequence.push_back(sommet);
	updateNonCouverts(sommet,graphe);
	deleteSommet(sommetsNonSelectionnes, sommet);
	sommetCourant = sommetsNonSelectionnes[rand() % sommetsNonSelectionnes.size()];
	localUpdate(sommet, evap, t0);
}


void Solution::deleteSommet(std::vector<Sommet*> &vector, Sommet* sommet) {
	for (int i = 0; i < vector.size(); i++)
	{
		if (sommet->getId() == vector[i]->getId())
		{
			vector.erase(vector.begin() + i);
		}
	}
}

void Solution::afficherSolution()
{
	std::cout << "{";
	for (int i = 0; i < sequence.size(); i++)
	{
		std::cout << sequence[i]->getId() << ", ";
	}
	std::cout << "}"  <<std::endl;
	std::cout << "Taille solution "+sequence.size() << std::endl;
}

void Solution::updateNonCouverts(Sommet* sommet,Graphe graphe) {
	std::vector<int> voisins = sommet->getVoisins();
	std::vector<Sommet*> sommetsCouverts;
	sommetsCouverts.push_back(sommet);
	for (int i = 0; i < voisins.size(); i++) {
		sommetsCouverts.push_back(graphe.getSommetFromId(voisins[i]));
	}
	for (int i = 0; i < sommetsNonCouverts.size(); i++) {
		for (int j = 0; j < sommetsCouverts.size(); j++) {
			if (sommetsNonCouverts[i]->getId() == sommetsCouverts[j]->getId()) {
				sommetsCouverts.erase(sommetsCouverts.begin()+j);
				sommetsNonCouverts.erase(sommetsNonCouverts.begin()+ i);
				i -= 1;
				break;
			}
		}
	}

}


int Solution::selection(std::vector<double> probs) {
	double random = rand()%RAND_MAX;
	for (int j = 0; j < probs.size(); j++) {
		if (j == probs.size() - 1) {
			return j;

		}
		else if (random >= probs[j] && random < probs[j + 1]) {
			return j;
		}
	}
	return -1;
}

void Solution::localUpdate(Sommet* sommet, double evap, double t0) {
	double trace = ( evap* sommet->getTrace()) + (1 - evap) * t0;
	sommet->setTrace(trace);
}

int Solution::FonctionObj() {
	return grapheSize/sequence.size();
}


int Solution::visibilite(Sommet* sommet,Graphe graphe) {
	std::vector<Sommet*> voisins = sommet->getPVoisins();
	int result = 0;
	for (int i = 0; i < sommetsNonCouverts.size(); i++) {
		Sommet* sommet =sommetsNonCouverts[i];
		for (int j = 0; j < voisins.size(); j++)
		{
			Sommet* voisin = voisins[j];
			if (sommet->getId() == voisin->getId()) {
				result++;
				voisins.erase(voisins.begin() + j);
				break;
			}
		}
	}
	return result;
}

bool Solution::dejaSelectionne(Sommet* sommet)
{
	for (int i = 0; i < sequence.size(); i++)
	{
		if ((*sommet).getId() == (*sequence[i]).getId())
			return true;
	}
	return false;
}

std::vector<Sommet*> Solution::voisinsValides(std::vector<Sommet*> voisins)
{
	std::vector<Sommet*> result;
	for (int i = 0; i < voisins.size(); i++)
	{
		Sommet* voisin = voisins[i];
		if (!dejaSelectionne(voisin))
		{
			result.push_back(voisin);
		}
	}
	return result;
}

bool Solution::valide() {
	return sommetsNonCouverts.size() == 0 ? true : false;
}

std::vector<Sommet*> Solution::getSequence()
{
	return sequence;
}

void Solution::setSequence(std::vector<Sommet*> sequenceP)
{
	Solution::sequence = sequenceP;
}

bool Solution::termine() {
	if (valide())
		return true;
	else return sommetsNonSelectionnes.size() == 0 ? true : false;
}

