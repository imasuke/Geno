// Selection.cpp
#include "Selection.h"
#include "Geeni/util.h"

#include <stdexcept>
#include <cmath>
#include <limits>

using std::vector;

namespace Geeni{
	Population rouletteSelection(const Population &org, unsigned int n, bool select_higher_fitness){
		Population select(n);
		vector<double> roulette(org.size());
		Randomizer rand;
		double sum = 0.0, max = 0.0;

		// check max fitness for minimaztion
		for(unsigned int i=0; i<org.size(); i++){
			if(max < org[i]->fitness) max = org[i]->fitness;
		}

		// calculate the sum of fitness for roulette
		for(unsigned int i=0; i<org.size(); i++){
			sum += (select_higher_fitness) ? org[i]->fitness : std::abs(org[i]->fitness - (max + 0.01));
		}
		if(sum == 0.0) throw std::runtime_error("Failed to execute roulette selection due to zero fitness");

		// prepare roulette
		for (unsigned int i=0; i<org.size(); i++){
			roulette[i] = (select_higher_fitness) ? org[i]->fitness / sum : std::abs(org[i]->fitness - (max + 0.01)) / sum;
		}
		// select individual by roulette
		for(unsigned int i=0; i<select.size(); i++){
			double r_sum = 0.0;
			double rand_real = rand.randomDouble(1.0);

			for (unsigned int j = 0; j < roulette.size(); j++){
				r_sum += roulette[j];
				if (r_sum > rand_real){
					select[i] = org[j]->clone();
					break;
				}
			}
		}
		return select;
	}

	Individual* rouletteSelection(const Population &org, bool select_higher_fitness){
		// select one individual by roulette selection
		Population pop = rouletteSelection(org, 1, select_higher_fitness);
		return pop[0];
	}

	Population tournamentSelection(const Population &org, unsigned int n, unsigned int tournament_size, bool select_higher_fitness){
		Population pop(n);

		for(unsigned int i=0; i<n; i++){
			pop[i] = tournamentSelection(org, tournament_size, select_higher_fitness);
		}
		return pop;
	}

	Individual* tournamentSelection(const Population &org, unsigned int tournament_size, bool select_higher_fitness){
		Randomizer rand;
		vector<int> tournament(tournament_size);
		double winner_fitness = (select_higher_fitness) ? 0.0 : std::numeric_limits<double>::max();
		unsigned int winner;

		// pick up tournament individuals randomly
		for(unsigned int i=0; i<tournament_size; i++){
			tournament[i] = rand.randomInt(org.size()-1);
		}
		// select winner fron tounament
		for(unsigned int i=0; i<tournament_size; i++){
			bool isWinnerFound = (select_higher_fitness) ? winner_fitness < org[tournament[i]]->fitness : winner_fitness > org[tournament[i]]->fitness;
			if(isWinnerFound){
				winner_fitness = org[tournament[i]]->fitness;
				winner = tournament[i];
			}
		}
		return org[winner];
	}
}