#pragma once
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

class Chronometre
{

	private:
		time_t debut;
		time_t fin;
		int tempsEcoule;

	public:
		Chronometre();
		~Chronometre();
		void start(std::string message);
		void stop(std::string message);
		void afficherTempsEcoule();
};

