#include "stdafx.h"
#include "ACO.h"

ACO::ACO()
{
}


ACO::~ACO()
{
}

Solution ACO::run(Graphe g) {
	Graphe graphe = g;
	Solution best;


	//Boucle principale
	for (int i = 0; i < nb_max_iterations; i++) {
		std::vector<Solution*> pop;
		std::vector<Solution*> result;
		for (int k = 0; k < pop_size; k++) {
			Solution* sol=new Solution();
			(*sol).initialize(graphe.getSommets());
			pop.push_back(sol);
		}
		int j = 0;

		//On construit les solutions, un pas a la fois
		while (pop.size()!=0) {
			if (j == pop.size())
			{
				j = 0;
			}
			Solution* current = pop[j];

			//Critere d'arret atteint
			if ((*current).termine()) {
				pop.erase(pop.begin() + j);
				result.push_back(current);
				if(j!=0)
					j--;
			}

			//pas suivant
			else
			{
				(*current).nextStep(graphe, evapLocal, t0, q, alpha);
				j++;
			}
		}

		//Mise a jour globale de la trace de pheromones
		Solution b=GlobalUpdate(result);
		if (best.getSequence().size()==0)
		{
			best = b;
		}
		else
		{
			//On garde la meilleure solution trouvée jusque la
			if (b.FonctionObj() > best.FonctionObj())
			{
				best = b;
			}
		}
	}
	//best.afficherSolution();
	int a = 0;
	return best;
}


Solution ACO::GlobalUpdate(std::vector<Solution*> pop)
{
	//Recherche de la meilleure solution
	Solution* bestSolution = pop[0];
	for (int i = 0; i < pop.size(); i++)
	{
		if ((*pop[i]).valide() && (*pop[i]).FonctionObj() > (*bestSolution).FonctionObj())
		{
			bestSolution = pop[i];
		}
	}

	//Mise a jour
	std::vector<Sommet*> sequence = (*bestSolution).getSequence();
	for (int i = 0; i < sequence.size(); i++)
	{
		Sommet* s = sequence[i];
		double trace= evapGlobal * s->getTrace() + ((1 - evapGlobal) * (t1/*/(*bestSolution).FonctionObj()*/));
		s->setTrace(trace);
	}
	return *bestSolution;
}
