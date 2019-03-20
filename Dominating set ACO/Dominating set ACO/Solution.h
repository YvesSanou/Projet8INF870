#pragma once
#include<vector>
#include "Sommet.h"
#include "Graphe.h"
#include "Math.h"


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
	void Solution::nextStep(Graphe graphe, double evap, double t0, double q, int alpha);
	void Solution::addSommet(Sommet sommet, Graphe graphe, double evap, double t0);
	void Solution::updateNonCouverts(Sommet sommet, Graphe graphe);
	int Solution::selection(std::vector<double> probs);
	void Solution::localUpdate(Sommet &sommet, double evap, double t0);
	int Solution::FonctionObj();
	int Solution::visibilite(Sommet sommet, Graphe graphe);
	bool Solution::valide();
	bool Solution::termine();
	void Solution::deleteSommet(std::vector<Sommet> &vector, Sommet sommet);
};

