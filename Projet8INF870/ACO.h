#pragma once
#include "Solution.h"
#include "Graphe.h"
#include "GenerateurInstances.h"


class ACO
{
private:
	int nb_max_iterations = 5;
	int pop_size = 5;
	double q = 0.9;
	double t0 = 0.1;
	double t1 = 1;
	double evapLocal = 0.4;
	double evapGlobal = 0.5;
	int alpha = 1;

public:
	ACO();
	~ACO();
	Solution ACO::run(Graphe g);
	Graphe ACO::instance_test();
	Solution ACO::GlobalUpdate(std::vector<Solution*> pop);
};
