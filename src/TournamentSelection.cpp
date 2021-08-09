// TournamentSelection.cpp
#include "Geno/AlternationModel.h" 
#include "Geno/util.h"
#include "Selection.h"

#include <algorithm>

using std::vector;

namespace Geno{
	TournamentSelection::TournamentSelection(unsigned int tournament_size, double crossover_rate, double mutation_rate) 
	: tournament_size_(tournament_size), crossover_rate_(crossover_rate), mutation_rate_(mutation_rate)
	{
	}

	TournamentSelection::~TournamentSelection(){
	}

	void TournamentSelection::alternatePopulation(Population *population, const OperatorSet &ops, bool is_maximize){
		ops_ = ops;

		// Select next population with tournament
		children_ = tournamentSelection(*population, population->size(), tournament_size_, is_maximize);
		// Crossover
		crossoverChildren(crossover_rate_);
		// Mutate
		mutateChildren(mutation_rate_);
		// Evaluation
		evaluateChildren();
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

		if(ops_.crossover->requiredParents() == 2){
			// 2 parents crossover
			Crossover2p *crossover = (Crossover2p*)ops_.crossover;

			// Choice the pair of individuals randomly
			for(unsigned int i=0; i < rand_indexes.size()/2; i++){
				if(rand.randomDouble(1.0) < crossover_rate){
					int ind1 = rand_indexes[2*i];
					int ind2 = rand_indexes[2*i+1];
					(*crossover)(children_[ind1], children_[ind2]);
				}
			}
		}
		else{
			// Todo
		}
	}
}
