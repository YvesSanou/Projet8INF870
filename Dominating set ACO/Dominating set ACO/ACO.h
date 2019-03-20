#pragma once
#include "Solution.h"
#include "Graphe.h"


class ACO
{
private:
	int nb_max_iterations = 20;
	int pop_size = 5;
	double q = 0;
	double t0 = 0.1;
	double evap = 0.5;
	int alpha = 1;

public:
	ACO();
	~ACO();
	void ACO::run();
	Graphe ACO::instance_test();
};
