// MGG.cpp
#include "Geno/AlternationModel.h" 
#include "Geno/util.h"
#include "Selection.h"

#include <algorithm>

using std::vector;

namespace Geno{
	MGG::MGG(size_t children_size) : children_size_(children_size){
	}

	MGG::~MGG(){
	}

	void MGG::makeChildren(Population *population, CrossoverOperator crossover, MutateOperator mutate, bool is_maximize){
		Population &pop = *population;
		Randomizer rand;
		crossover_ = crossover;
		mutate_ = mutate;

		// choice 2 different individuals as parents
		unsigned int p1, p2;
		do{
			p1 = rand.randomInt(pop.size()-1);
			p2 = rand.randomInt(pop.size()-1);
		} while(p1 == p2);

		// copy parents to children
		Individual *parent1 = pop[p1], *parent2 = pop[p2];
		children_.resize(children_size_);
		for(unsigned int i=0; i<children_.size(); i++){
			if(i % 2)
				children_[i] = parent1->clone();
			else
				children_[i] = parent2->clone();
		}

		// crossover
		for(unsigned int i=1; i<children_.size()/2; i++){
			crossover_(children_[2*i], children_[2*i+1]);
		}

		// delete parents from original population
		pop.erase(std::remove(pop.begin(), pop.end(), parent1), pop.end());
		pop.erase(std::remove(pop.begin(), pop.end(), parent2), pop.end());
	}

	void MGG::alternatePopulation(Population *population, bool is_maximize){
		Individual *elite, *roulette;

		elite = findElite(is_maximize);
		roulette = rouletteSelection(children_, is_maximize);
		population->push_back(elite);
		population->push_back(roulette);
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