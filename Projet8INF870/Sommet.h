#pragma once
#include <vector>

class Sommet
{

protected:
	int id;
	double trace;
	std::vector<int> voisins;

public:
	Sommet();
	Sommet(int id);
	int Sommet::getId();
	void Sommet::setId(int id);
	std::vector<int> Sommet::getVoisins();
	void setVoisins(std::vector<int> voisins);
	void Sommet::addVoisin(int voisin);
	double Sommet::getTrace();
	void Sommet::setTrace(double trace);
	~Sommet();
};

