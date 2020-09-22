// AllOneBitString.cpp
#include <iostream>
#include <vector>

#include "Geeni.h"
#include "matplotlib-cpp/matplotlibcpp.h"

using std::vector;
using namespace Geeni;
namespace plt = matplotlibcpp;

double countOneBit(const Individual &ind){
	BinaryArrayIndividual &bind = (BinaryArrayIndividual&)ind;
	int count = 0;

	for(unsigned int i=0; i<bind.genotype.size(); i++){
		if(bind.genotype[i]) count++;
	}
	return (double)count / bind.genotype.size();
}

class MyObserver : public Observer{
	void generationAltered(GA *ga){
		int gen = ga->getCurrentGeneration();
		std::cout << "gen:" << gen << " elite:" << ga->getEliteIndividual()->fitness << std::endl;

		if(gen % 100 == 0){
			vector<double> x(gen), means, max;
			Statistics *stat = ga->getStatistics();

			std::iota(x.begin(), x.end(), 0);
			means = stat->meanFitnessReport();
			max = stat->maxFitnessReport();

			plt::clf();
			plt::named_plot("Fitness(Mean)", x, means);
			plt::named_plot("Fitness(Max)", x, max);
			plt::xlim(0, gen);
			plt::title("Fitness transition");
			plt::legend();
			plt::pause(0.01);
		}
	}
	
	void evolutionEnded(GA *ga){
		BinaryArrayIndividual *best = (BinaryArrayIndividual*) ga->getEliteIndividual();
		std::cout << "best fitness: " << best->fitness << std::endl;
		std::cout << "best: " ;
		for(unsigned int i=0; i<best->genotype.size(); i++){
			std::cout << (best->genotype[i] ? 1:0) ;
		}
		std::cout << std::endl;
	}
};

int main(void){
	BinaryArrayIndividual::Factory factory;
	factory.geneSize(100)
		.initializer(BinaryArrayIndividual::randomInitializer)
		.crossover(BinaryArrayIndividual::uniformCrossover)
		.mutate(BinaryArrayIndividual::randomMutate);
	GA ga(factory, countOneBit);
	MyObserver observer;
	GA::Parameter param;
	RouletteSelection roulette;

	param.population_size = 100;
	param.max_generation = 100000;
	param.goal_fitness = 1.0;
	ga.setParameter(param);
	ga.setAlternationModel(roulette);
	ga.addObserver(observer);
	ga.enableStatistics(true);

	ga.evolve();
	getchar();

	return 0;
}

