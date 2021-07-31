// MGG.cpp
#include "Geno/AlternationModel.h" 
#include "Geno/util.h"
#include "Selection.h"

#include <algorithm>

using std::vector;

namespace Geno{
	MGG::MGG(size_t children_size, double mutation_rate) : children_size_(children_size), mutation_rate_(mutation_rate){
	}

	MGG::~MGG(){
	}

	void MGG::makeChildren(Individual *parent1, Individual *parent2){
		// copy parents to children
		children_.resize(children_size_);
		for(unsigned int i=0; i<children_.size(); i++){
			if(i % 2)
				children_[i] = parent1->clone();
			else
				children_[i] = parent2->clone();
		}
		// crossover
		for(unsigned int i=1; i<children_.size()/2; i++){
			(*ops_.crossover)(children_[2*i], children_[2*i+1]);
		}
	}

	void MGG::alternatePopulation(Population *population, const OperatorSet &ops, const bool is_maximize){
		Individual *parent1, *parent2, *elite, *roulette;
		Population &pop = *population;
		Randomizer rand;
		ops_ = ops;

		// choice 2 different individuals as parents
		unsigned int p1, p2;
		do{
			p1 = rand.randomInt(pop.size()-1);
			p2 = rand.randomInt(pop.size()-1);
		} while(p1 == p2);
		parent1 = pop[p1];
		parent2 = pop[p2];

		// make childres from parents
		makeChildren(parent1, parent2);
		// delete parents from original population
		pop.erase(std::remove(pop.begin(), pop.end(), parent1), pop.end());
		pop.erase(std::remove(pop.begin(), pop.end(), parent2), pop.end());
		// mutation
		mutateChildren(mutation_rate_);
		// evaluation
		evaluateChildren();

		// add new 2 individuals to the population
		elite = findElite(is_maximize);
		roulette = rouletteSelection(children_, is_maximize);
		pop.push_back(elite);
		pop.push_back(roulette);
	}

	Individual* MGG::findElite(bool is_maximize){
		double elite_fitnesss = (is_maximize) ? 0.0 : std::numeric_limits<double>::max();
		unsigned int i_elite = 0;

		for(unsigned int i=0; i<children_.size(); i++){
			bool isEliteFound = (is_maximize && children_[i]->fitness > elite_fitnesss) // Maximaization
				|| (!is_maximize && children_[i]->fitness < elite_fitnesss); // Minimaization

			if(isEliteFound){
				elite_fitnesss = children_[i]->fitness;
				i_elite = i;
			}
		}
		return children_[i_elite];
	}
}