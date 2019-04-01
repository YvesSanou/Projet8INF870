#pragma once
#include <vector>

class Sommet
{

protected:
	int id;
	double trace;
	std::vector<Sommet*> pvoisins;
	std::vector<int> voisins;
	std::vector<int> superVoisins;

public:
	Sommet();
	Sommet(int id);
	int Sommet::getId();
	void Sommet::setId(int id);
	std::vector<int> Sommet::getVoisins();
	std::vector<int> Sommet::getSuperVoisins();
	void Sommet::initSuperVoisins();
	void Sommet::setSuperVoisins(std::vector<int> superVoisinsP);
	void Sommet::deleteSuperVoisinFromId(int id);
	void setVoisins(std::vector<int> voisins);
	void setPVoisins(std::vector<Sommet*> voisins);
	std::vector<Sommet*> getPVoisins();
	void Sommet::addVoisin(int voisin);
	double Sommet::getTrace();
	void Sommet::setTrace(double trace);
	~Sommet();
};

