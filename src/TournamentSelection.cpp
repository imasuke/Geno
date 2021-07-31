// TournamentSelection.cpp
#include "Geno/AlternationModel.h" 
#include "Geno/util.h"
#include "Selection.h"

#include <algorithm>

using std::vector;

namespace Geno{
	TournamentSelection::TournamentSelection(unsigned int tournament_size) 
	: tournament_size_(tournament_size)
	{
	}

	TournamentSelection::~TournamentSelection(){
	}

	void TournamentSelection::makeChildren(Population *population, CrossoverOperator crossover, MutateOperator mutate, bool is_maximize){
		crossover_ = crossover;
		mutate_ = mutate;
		children_ = tournamentSelection(*population, population->size(), tournament_size_, is_maximize);
		crossoverChildren(0.8); //TODO
	}

	void TournamentSelection::alternatePopulation(Population *population, bool is_maximize){
		// replace all population with children
		*population = children_;
	}

	void TournamentSelection::crossoverChildren(double crossover_rate){
		Randomizer rand;
		vector<int> rand_indexes;

		// Preapare the arrray that stores population indexes with random order
		rand_indexes.resize(children_.size());
		std::iota(rand_indexes.begin(), rand_indexes.end(), 0);
		std::random_device rd;
		std::shuffle(rand_indexes.begin(), rand_indexes.end(), std::mt19937(rd()));

		// Choice the pair of individuals randomly
		for(unsigned int i=0; i < rand_indexes.size()/2; i++){
			if(rand.randomDouble(1.0) < crossover_rate){
				int ind1 = rand_indexes[2*i];
				int ind2 = rand_indexes[2*i+1];
				crossover_(children_[ind1], children_[ind2]);
			}
		}
	}
}
