// Individual.h
#ifndef INDIVIDUAL_HEADER
#define INDIVIDUAL_HEADER

#include <vector>
#include <functional>

namespace Geeni{
	class Individual;
	typedef std::function <void(Individual*, Individual*)> CrossoverOperator;
	typedef std::function <void(Individual*)> MutateOperator;
	typedef std::function <double(const Individual&)> FitnessFunction;
	typedef std::vector<Individual*> Population;

	// Abstract Individual class
	class Individual{
	public:
		Individual(const CrossoverOperator crossover, const MutateOperator mutate) :
		 fitness(0.0), crossover(crossover), mutate(mutate) {}
		Individual(const Individual &c) {
			fitness = c.fitness;
			crossover = c.crossover;
			mutate = c.mutate;
		}
		virtual ~Individual(){}
		virtual Individual* clone() = 0;

	public:
		double fitness;
		CrossoverOperator crossover;
		MutateOperator mutate;
	};

	// Abstract Factory class
	class IndividualFactory{
	public:
		IndividualFactory(){}
		virtual ~IndividualFactory(){}
		virtual Individual* create() = 0; 
	};
}

#endif