#include "stdafx.h"
#include "Solution.h"
#include "Sommet.h"
#include "Graphe.h"
#include "Math.h"


Solution::Solution()
{
}


Solution::~Solution()
{
}

void Solution::initialize(std::vector<Sommet> sommets) {
	sommetsNonSelectionnes = sommets;
	sommetsNonCouverts = sommets;
}

void Solution::nextStep(double evap, double t0, double q, int alpha) {
	double random = rand() % RAND_MAX;
	Sommet selection;
	if (random > q) {
		selection = sommetsNonSelectionnes[0];
		int vis = visibilite(selection.getVoisins());
		double value = selection.getTrace() * (pow(vis, alpha));
		for (int i = 1; i < sommetsNonSelectionnes.size(); i++) {
			Sommet current = sommetsNonSelectionnes[i];
			vis = visibilite(current.getVoisins());
			double temp = current.getTrace() * (pow(vis, alpha));
			if (temp > value) {
				value = temp;
				selection = current;
			}
		}
	}
	else {
		std::vector<double> probs = std::vector<double>();
		for (int i = 0; i < sommetsNonSelectionnes.size(); i++) {
			Sommet sommet = sommetsNonSelectionnes[i];
			int vis = visibilite(sommet.getVoisins());
			double trace = sommet.getTrace();
			double value = trace * pow(vis, alpha);
			probs.push_back(value);
		}
		double probSum = 0;
		for (int i = 0; i < probs.size(); i++) {
			probSum += probs[i];
		}
		for (int i = 0; i < probs.size(); i++) {
			double prob = probs[i];
			prob = prob / probSum;
		}
		int index = Solution::selection(probs);
		selection = sommetsNonSelectionnes[index];
		int a = 0;
	}
	addSommet(selection, evap, t0);
}

void Solution::addSommet(Sommet sommet, double evap, double t0) {
	sequence.push_back(sommet);
	updateNonCouverts(sommet);
	deleteSommet(sommetsNonSelectionnes, sommet);
	localUpdate(sommet, evap, t0);
}


void Solution::deleteSommet(std::vector<Sommet> &vector,Sommet sommet) {
	for (int i = 0; i < vector.size(); i++)
	{
		if (sommet.getId() == vector[i].getId())
		{
			vector.erase(vector.begin() + i);
		}
	}
}

void Solution::updateNonCouverts(Sommet sommet) {
	std::vector<Sommet> voisins = sommet.getVoisins();
	std::vector<Sommet> sommetsCouverts;
	sommetsCouverts.push_back(sommet);
	for (int i = 0; i < voisins.size(); i++) {
		sommetsCouverts.push_back(voisins[i]);
	}
	for (int i = 0; i < sommetsNonCouverts.size(); i++) {
		for (int j = 0; j < sommetsCouverts.size(); j++) {
			if (sommetsNonCouverts[i].getId() == sommetsCouverts[j].getId()) {
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

void Solution::localUpdate(Sommet &sommet, double evap, double t0) {
	double trace = ((1 - evap) * sommet.getTrace()) + evap * t0;
	sommet.setTrace(trace);
}

int Solution::FonctionObj() {
	return sequence.size();
}


int Solution::visibilite(std::vector<Sommet> voisins) {

	int result = 0;
	for (int i = 0; i < sommetsNonCouverts.size(); i++) {
		Sommet sommet =sommetsNonCouverts[i];
		for (int j = 0; j < voisins.size(); j++)
			if (sommet.getId() == voisins[j].getId()) {
				result++;
				voisins.erase(voisins.begin()+j);
				break;
			}
	}
	return result;
}

bool Solution::valide() {
	return sommetsNonCouverts.size() == 0 ? true : false;
}

std::vector<Sommet> Solution::getSequence()
{
	return sequence;
}

void Solution::setSequence(std::vector<Sommet> sequenceP)
{
	Solution::sequence = sequenceP;
}

bool Solution::termine() {
	if (valide())
		return true;
	else return sommetsNonSelectionnes.size() == 0 ? true : false;
}

