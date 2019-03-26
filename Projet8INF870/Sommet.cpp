#include "stdafx.h"
#include "Sommet.h"
#include <vector>


Sommet::Sommet()
{

}

Sommet::Sommet(int value)
{
	id = value;
}

int Sommet::getId() {
	return id;
}

void Sommet::setId(int value) {
	id = value;
}

std::vector<int> Sommet::getVoisins() {
	return voisins;
}

std::vector<int> Sommet::getSuperVoisins()
{
	return superVoisins;
}

void Sommet::initSuperVoisins()
{
	superVoisins = voisins;
	superVoisins.push_back(id);
}

void Sommet::setSuperVoisins(std::vector<int> superVoisinsP)
{
	superVoisins = superVoisinsP;
}

void Sommet::deleteSuperVoisinFromId(int id)
{
	int index = 0;
	for (int i = 0; i < superVoisins.size(); i++)
	{
		if (superVoisins[i] == id)
		{
			index = i;
			break;
		}
	}
	superVoisins.erase(superVoisins.begin()+index);

}

void Sommet::setVoisins(std::vector<int> value) {
	voisins = value;
}
void Sommet::addVoisin(int voisin)
{
	voisins.push_back(voisin);
}

double Sommet::getTrace() {
	return trace;
}

void Sommet::setTrace(double value) {
	trace = value;
}

Sommet::~Sommet()
{
}
