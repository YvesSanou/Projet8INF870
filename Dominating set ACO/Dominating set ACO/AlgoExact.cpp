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
	Solution s;

	//Find all subsets
	int n = graphe.getSommets().size;
	int  count = pow(2, graphe.getSommets().size);
	for (int i = 0; i < count; i++)
	{
		//Generate a subset
		std::vector<Sommet> subset;
		for (int j = 0; j < n; j++)
		{
			// This if condition will check if jth bit in binary representation of  i  is set or not
			// if the value of (i & (1 << j)) is greater than 0 , include arr[j] in the current subset
			// otherwise exclude arr[j]
			if ((i & (1 << j)) > 0)
			{
				subset.push_back(graphe.getSommets()[j]);
			}
		}

		//Use the subset to construct a Solution
		Solution s;
		s.setSequence(subset);

		//Test the solution
		if (graphe.solutionValide(s))
		{
			break;
			break;
		}
	}

	return s;
}
