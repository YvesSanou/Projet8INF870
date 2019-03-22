#include "stdafx.h"
#include "ACO.h"

ACO::ACO()
{
}


ACO::~ACO()
{
}

void ACO::run() {
	GenerateurInstances gen;
	Graphe graphe = gen.donnerExemple();
	Solution best;

	for (int i = 0; i < nb_max_iterations; i++) {
		std::vector<Solution*> pop;
		std::vector<Solution*> result;
		for (int k = 0; k < pop_size; k++) {
			Solution* sol=new Solution();
			(*sol).initialize(graphe.getSommets());
			pop.push_back(sol);
		}
		int j = 0;
		while (pop.size()!=0) {
			if (j == pop.size())
			{
				j = 0;
			}
			Solution* current = pop[j];
			if ((*current).termine()) {
				pop.erase(pop.begin() + j);
				result.push_back(current);
				if(j!=0)
					j--;
			}
			else
			{
				(*current).nextStep(graphe, evapLocal, t0, q, alpha);
				j++;
			}
		}
		Solution b=GlobalUpdate(result);
		if (best.getSequence().size()==0)
		{
			best = b;
		}
		else
		{
			if (b.FonctionObj() > best.FonctionObj())
			{
				best = b;
			}
		}
	}
	best.afficherSolution();
	int a = 0;
}


Solution ACO::GlobalUpdate(std::vector<Solution*> pop)
{
	Solution* bestSolution = pop[0];
	for (int i = 0; i < pop.size(); i++)
	{
		if ((*pop[i]).valide() && (*pop[i]).FonctionObj() > (*bestSolution).FonctionObj())
		{
			bestSolution = pop[i];
		}
	}
	std::vector<Sommet*> sequence = (*bestSolution).getSequence();
	for (int i = 0; i < sequence.size(); i++)
	{
		Sommet* s = sequence[i];
		double trace= evapGlobal * s->getTrace() + ((1 - evapGlobal) * (t1/(*bestSolution).FonctionObj()));
		s->setTrace(trace);
	}
	return *bestSolution;
}

Graphe ACO::instance_test() {
	Graphe result;
	Sommet* S1 = new Sommet(1);
	S1->setTrace(t0);
	Sommet* S2 = new Sommet(2);
	S2->setTrace(t0);
	Sommet* S3 = new Sommet(3);
	S3->setTrace(t0);
	Sommet* S4 = new Sommet(4);
	S4->setTrace(t0);
	Sommet* S5 = new Sommet(5);
	S5->setTrace(t0);

	S1->addVoisin(S3->getId());
	S2->addVoisin(S4->getId());
	S3->addVoisin(S5->getId());
	S3->addVoisin(S1->getId());
	S4->addVoisin(S5->getId());
	S4->addVoisin(S2->getId());
	S5->addVoisin(S1->getId());
	S5->addVoisin(S4->getId());
	S5->addVoisin(S3->getId());
	std::vector<Sommet*> sommets;
	sommets.push_back(S1);
	sommets.push_back(S2);
	sommets.push_back(S3);
	sommets.push_back(S4);
	sommets.push_back(S5);
	result.setSommets(sommets);
	return result;
}