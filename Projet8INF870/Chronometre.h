#pragma once
#include <chrono>
#include <ctime>
#include <iostream>

class Chronometre
{

	private:
		time_t debut;
		time_t fin;
		int tempsEcoule;

	public:
		Chronometre();
		~Chronometre();
		void start();
		void stop();
		void afficherTempsEcoule();
};

