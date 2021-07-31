// GA.cpp
#include "Geno/GA.h"
#include "Geno/util.h"
#include <vector>
#include <limits>

using std::vector;

namespace Geno{
	GA::GA(IndividualFactory &factory, FitnessFunction ff){
		this->factory = &factory;
		this->ff = ff;
		this->alt_model = new RouletteSelection(); // Default
		this->param = new GA::Parameter();
		this->gen = 0;
		this->elite = nullptr;
		this->observer = nullptr;
		this->stat = nullptr;
		this->statistics_enabled = false;
	}

	GA::~GA(){
		this->factory = nullptr;
		this->ff = nullptr;
		this->alt_model = nullptr;
		this->param = nullptr;
		this->elite = nullptr;
		this->observer = nullptr;
		if(stat) delete this->stat;
	}

	void GA::evolve(){
		bool is_goal_reached = false;
		AlternationModel::OperatorSet ops = {factory->crossover(), factory->mutate(), ff};

		initPopulation();
		evaluatePopulation(&population);

		gen = 1;
		observer->evolutionStarted(this);

		do{
			/*alt_model->makeChildren(&population, factory->crossover(), factory->mutate(), param->is_maximize);
			alt_model->mutateChildren(param->mutation_rate);
			alt_model->evaluateChildren(ff);*/
			alt_model->alternatePopulation(&population, ops, param->is_maximize);
			if(param->elite_strategy) eliteStrategy();
			elite = findElite(param->is_maximize);
			if(statistics_enabled) stat->collectPopulationData(population);
			observer->generationAltered(this);
			gen++;
			is_goal_reached = (param->is_maximize && elite->fitness >= param->goal_fitness) // Maximaization
				|| (!param->is_maximize && elite->fitness <= param->goal_fitness); // Minimaization
		} while(!is_goal_reached && gen <= param->max_generation);
		observer->evolutionEnded(this);
	}

	void GA::addObserver(Observer &observer){
		this->observer = &observer;
	}

	void GA::removeObserver(){
		this->observer = nullptr;
	}

	void GA::setParameter(Parameter& param){
		this->param = &param;	
	}

	GA::Parameter GA::getParameter() const{
		return *param;
	}

	Population GA::getPopulation() const{
		return population;
	}

	Statistics* GA::getStatistics() const{
		return stat;
	}

	void GA::setAlternationModel(AlternationModel &gt_model){
		this->alt_model = &gt_model;
	}

	void GA::setFitnessFuction(FitnessFunction ff){
		this->ff = ff;
	}

	int GA::getCurrentGeneration() const{
		return gen;
	}

	Individual* GA::getEliteIndividual() const{
		return elite;
	}

	void GA::enableStatistics(bool flag){
		if(flag && !statistics_enabled){
			stat = new Statistics();
		}
		else if(!flag && statistics_enabled){
			delete stat;
			stat = nullptr;
		}
		statistics_enabled = flag;
	}

	void GA::initPopulation(){
		population.resize(param->population_size);
		for(unsigned int i=0; i<population.size(); i++){
			population[i] = factory->create();
		}
	}

	void GA::evaluatePopulation(Population *population){
		for(unsigned int i=0; i<population->size(); i++){
			population->at(i)->fitness = ff(*(population->at(i)));
		}
	}

	void GA::eliteStrategy(){
		if(elite){
			population[0] = elite;
		}
	}

	Individual* GA::findElite(bool is_maximize){
		double elite_fitnesss = (is_maximize) ? 0.0 : std::numeric_limits<double>::max();
		unsigned int i_elite = 0;

		for(unsigned int i=0; i<population.size(); i++){
			bool isEliteFound = (is_maximize && population.at(i)->fitness > elite_fitnesss) // Maximaization
				|| (!is_maximize && population.at(i)->fitness < elite_fitnesss); // Minimaization

			if(isEliteFound){
				elite_fitnesss = population.at(i)->fitness;
				i_elite = i;
			}
		}

		return population.at(i_elite)->clone();
	}
}

