// RouletteSelection.cpp
#include "Geno/AlternationModel.h" 
#include "Geno/util.h"
#include "Selection.h"

#include <algorithm>

using std::vector;

namespace Geno{
	RouletteSelection::RouletteSelection()
	 : crossover_rate_(0.8), mutation_rate_(0.05){
	}	

	RouletteSelection::RouletteSelection(double crossover_rate, double mutation_rate)
	 : crossover_rate_(crossover_rate), mutation_rate_(mutation_rate){
	}

	RouletteSelection::~RouletteSelection(){
	}

	void RouletteSelection::alternatePopulation(Population *population, const OperatorSet &ops, const bool is_maximize){
		ops_ = ops;

		// Select next population with roulette
		children_ = rouletteSelection(*population, population->size(), is_maximize);
		// Crossover
		crossoverChildren(crossover_rate_);
		// Mutate
		mutateChildren(mutation_rate_);
		// Evaluation
		evaluateChildren();
		// replace all population with children
		*population = children_;
	}

	void RouletteSelection::crossoverChildren(double crossover_rate){
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
				(*ops_.crossover)(children_[ind1], children_[ind2]);
			}
		}
	}
}