#include "stdafx.h"
#include "AlgoExact.h"
#include "Sommet.h"
#include <iostream>


AlgoExact::AlgoExact()
{

}


AlgoExact::~AlgoExact()
{
}

Solution AlgoExact::resoudreGraphe(Graphe graphe)
{
	Solution solutionFinale;
	Solution s;
	int n = graphe.getSommets().size();
	int nSub = 1 << n;
	for (int i = 0; i < nSub; i++)
	{
		//Generate a subset
		std::vector<Sommet*> subset;
		for (int k = 0; k < n; k++)
		{
			//if the k-th bit is set
			if ((1 << k) & i)
			{
				subset.push_back(graphe.getSommets()[k]);
			}
		}

		//Use the subset to construct a Solution
		s.setSequence(subset);
		s.afficherSolution();

		//Test the solution
		if ( graphe.solutionValide(s) && (s.getSequence().size() < solutionFinale.getSequence().size() || solutionFinale.getSequence().size() == 0))
		{
			solutionFinale = s;
			std::cout << "Oh, une meilleure solution!" << std::endl;
			solutionFinale.afficherSolution();
		}
	}

	return solutionFinale;
}
