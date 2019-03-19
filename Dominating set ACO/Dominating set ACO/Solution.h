#pragma once
#include<vector>
#include "Sommet.h"


class Solution
{
private:
	double fonctionObjective;
	std::vector<Sommet> sequence;
	std::vector<Sommet> sommetsNonSelectionnes;
	std::vector<Sommet> sommetsNonCouverts;

public:
	Solution();
	~Solution();
	void Solution::initialize(std::vector<Sommet> sommets);
	void Solution::nextStep(double evap, double t0, double q, int alpha);
	void Solution::addSommet(Sommet sommet, double evap, double t0);
	void Solution::updateNonCouverts(Sommet sommet);
	int Solution::selection(std::vector<double> probs);
	void Solution::localUpdate(Sommet &sommet, double evap, double t0);
	int Solution::FonctionObj();
	int Solution::visibilite(std::vector<Sommet> voisins);
	bool Solution::valide();
	bool Solution::termine();
	void Solution::deleteSommet(std::vector<Sommet> &vector, Sommet sommet);
};

