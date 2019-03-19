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

std::vector<Sommet> Sommet::getVoisins() {
	return voisins;
}

void Sommet::setVoisins(std::vector<Sommet> voisins) {
	voisins = voisins;
}
void Sommet::addVoisin(Sommet voisin)
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
