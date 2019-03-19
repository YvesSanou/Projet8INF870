#pragma once
#include <vector>

class Sommet
{

protected:
	int id;
	double trace;
	std::vector<Sommet> voisins;

public:
	Sommet();
	Sommet(int id);
	int Sommet::getId();
	void Sommet::setId(int id);
	std::vector<Sommet> Sommet::getVoisins();
	void setVoisins(std::vector<Sommet> voisins);
	void Sommet::addVoisin(Sommet voisin);
	double Sommet::getTrace();
	void Sommet::setTrace(double trace);
	~Sommet();
};

