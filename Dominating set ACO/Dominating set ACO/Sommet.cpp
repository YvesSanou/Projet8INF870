#include "stdafx.h"
#include "Sommet.h"
#include <vector>


Sommet::Sommet()
{

}

Sommet::Sommet(int temp)
{
	id = temp;
}

int Sommet::getId() {
	return id;
}

void Sommet::setId(int id) {
	id = id;
}

std::vector<int> Sommet::getVoisins() {
	return voisins;
}

void Sommet::setVoisins(std::vector<int> voisins) {
	voisins = voisins;
}
void Sommet::addVoisin(int voisin)
{
	voisins.push_back(voisin);
}

double Sommet::getTrace() {
	return trace;
}

void Sommet::setTrace(double trace) {
	trace = trace;
}

Sommet::~Sommet()
{
}
