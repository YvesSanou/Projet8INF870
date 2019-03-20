#include "stdafx.h"
#include "ACO.h"

ACO::ACO()
{
}


ACO::~ACO()
{
}

void ACO::run() {
	Graphe graphe = instance_test();
	Solution best;

	for (int i = 0; i < nb_max_iterations; i++) {
		std::vector<Solution> pop;
		std::vector<Solution> result;
		for (int k = 0; k < pop_size; k++) {
			Solution sol;
			sol.initialize(graphe.getSommets());
			pop.push_back(sol);
		}

		Solution current = pop[0];
		while (!current.termine()) {
			//for (int j = 0; j < pop.size(); j++) {
			//Solution current = pop.get(0);
			/*if (current.termine()) {
			pop.remove(current);
			result.add(current);
			} else
			current.nextStep(graphe,evap, t0, q, graphe, alpha);
			//}*/
			current.nextStep(graphe, evap, t0, q, alpha);
		}
		int a = 0;

	}
}

Graphe ACO::instance_test() {
	Graphe result;
	Sommet S1(1);
	S1.setTrace(t0);
	Sommet S2(2);
	S2.setTrace(t0);
	Sommet S3(3);
	S3.setTrace(t0);
	Sommet S4(4);
	S4.setTrace(t0);
	Sommet S5(5);
	S5.setTrace(t0);

	S1.addVoisin(S3.getId());
	S2.addVoisin(S4.getId());
	S3.addVoisin(S5.getId());
	S3.addVoisin(S1.getId());
	S4.addVoisin(S5.getId());
	S4.addVoisin(S2.getId());
	S5.addVoisin(S1.getId());
	S5.addVoisin(S4.getId());
	S5.addVoisin(S3.getId());
	std::vector<Sommet> sommets;
	sommets.push_back(S1);
	sommets.push_back(S2);
	sommets.push_back(S3);
	sommets.push_back(S4);
	sommets.push_back(S5);
	result.setSommets(sommets);
	return result;
}