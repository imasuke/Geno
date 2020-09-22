// Statistics.cpp

#include "Geeni/Statistics.h"
#include <iostream>
#include <limits>

using std::vector;

namespace Geeni{
	Statistics::Statistics(){
	}

	Statistics::~Statistics(){
		maxFitness.clear();
		minFitness.clear();
		meanFitnesss.clear();
	}

	vector<double> Statistics::maxFitnessReport(){
		return maxFitness;
	}

	vector<double> Statistics::minFitnessReport(){
		return minFitness;
	}

	vector<double> Statistics::meanFitnessReport(){
		return meanFitnesss;
	}

	void Statistics::collectPopulationData(const vector<Individual*> &population){
		double max, min, sum;
		max = std::numeric_limits<double>::min();
		min = std::numeric_limits<double>::max();
		sum = 0.0;

		for(size_t i=0; i<population.size(); i++){
			sum += population[i]->fitness;
			if(max < population[i]->fitness){
				max = population[i]->fitness;
			}
			if(min > population[i]->fitness){
				min = population[i]->fitness;
			}
		}
		maxFitness.push_back(max);
		minFitness.push_back(min);
		meanFitnesss.push_back(sum / population.size());
	}
}