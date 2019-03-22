#pragma once
#include "Sommet.h"
#include "Graphe.h"

class AlgoExact
{
	public:
		AlgoExact();
		~AlgoExact();
		Solution resoudreTrivial(Graphe graphe);
		Solution resoudreReed(Graphe graphe);
		Solution resoudreGrandoni(Graphe graphe);
};

