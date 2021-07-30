// BenchmarkFunction.cpp
#include <iostream>
#include <vector>

#include "Geeni.h"
#include "matplotlib-cpp/matplotlibcpp.h"

using std::vector;
using namespace Geeni;
namespace plt = matplotlibcpp;

double sphere(const Individual &ind){
	RealVectorIndividual &rind = (RealVectorIndividual&)ind;
	double sum = 0.0;

	for(size_t i=0; i<rind.genotype.size(); i++){
		sum += rind.genotype[i] * rind.genotype[i];
	}
	return sum;
}

double rosenbrock(const Individual &ind){
	RealVectorIndividual &rind = (RealVectorIndividual&)ind;
	double sum = 0.0;

	for(size_t i=0; i<rind.genotype.size()-1; i++){
		double p1 = rind.genotype[i+1] - rind.genotype[i] * rind.genotype[i];
		double p2 = 1.0 - rind.genotype[i];
		sum += 100 * p1 * p1 + p2 * p2;
	}
	return sum;
}

class MyObserver : public Observer{
	void generationAltered(GA *ga){
		int gen = ga->getCurrentGeneration();
		std::cout << "gen:" << gen << " elite:" << ga->getEliteIndividual()->fitness << std::endl;

		if(gen % 100 == 0){
			Population p = ga->getPopulation();
			vector<double> x(p.size()), y(p.size());

			for(unsigned int i=0; i<p.size(); i++){
				RealVectorIndividual *ind = (RealVectorIndividual*)p[i];
				x[i] = ind->genotype[0];
				y[i] = ind->genotype[1];
			}
			plt::clf();
			plt::xlim(-50, 50);
			plt::ylim(-50, 50);
			plt::scatter(x, y, 10);
			plt::grid(true);
			plt::title("Rosenbrock function");
			plt::pause(0.01);
		}
	}
	
	void evolutionEnded(GA *ga){
		RealVectorIndividual *best = (RealVectorIndividual*) ga->getEliteIndividual();
		std::cout << "best fitness: " << best->fitness << std::endl;
		std::cout << "best: " ;
		for(unsigned int i=0; i<best->genotype.size(); i++){
			std::cout << best->genotype[i] << " " ;
		}
		std::cout << std::endl;
	}
};

int main(void){
	RealVectorIndividual::Factory factory;
	factory.geneSize(2)
		.initializer(RealVectorIndividual::randomInitializer(-100, 100))
		.crossover(RealVectorIndividual::blxAlphaCrossover())
		.mutate(RealVectorIndividual::randomMutate(-100, 100));
	GA ga(factory, rosenbrock);
	MyObserver observer;
	GA::Parameter param;
	MGG mgg(20); // Minimal Generation Gap

	param.population_size = 100;
	param.max_generation = 10000;
	param.goal_fitness = 0.0;
	param.is_maximize = false; // Fitness should be minimized
	ga.setParameter(param);
	ga.setAlternationModel(mgg);
	ga.addObserver(observer);
	ga.enableStatistics(true);

	ga.evolve();
	getchar();

	return 0;
}

