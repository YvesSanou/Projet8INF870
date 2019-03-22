#pragma once
#include<vector>
#include "Sommet.h"
#include "Graphe.h"
#include "Math.h"
class Graphe;


class Solution
{
private:
	double fonctionObjective;
	std::vector<Sommet*> sequence;
	std::vector<Sommet*> sommetsNonSelectionnes;
	std::vector<Sommet*> sommetsNonCouverts;

public:
	Solution();
	~Solution();
	void initialize(std::vector<Sommet*> sommets);
	void nextStep(Graphe graphe, double evap, double t0, double q, int alpha);
	void addSommet(Sommet* sommet, Graphe graphe, double evap, double t0);
	void updateNonCouverts(Sommet* sommet, Graphe graphe);
	int selection(std::vector<double> probs);
	void localUpdate(Sommet* sommet, double evap, double t0);
	int FonctionObj();
	int visibilite(Sommet* sommet, Graphe graphe);
	bool valide();
	std::vector<Sommet*> getSequence();
	void setSequence(std::vector<Sommet*> sequenceP);
	bool termine();
	void deleteSommet(std::vector<Sommet*> &vector, Sommet* sommet);
	void afficherSolution();
};

