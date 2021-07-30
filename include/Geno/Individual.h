// Individual.h
#ifndef INDIVIDUAL_HEADER
#define INDIVIDUAL_HEADER

#include <vector>
#include <functional>

namespace Geno{
	class Individual;
	typedef std::function <void(Individual*, Individual*)> CrossoverOperator;
	typedef std::function <void(Individual*)> MutateOperator;
	typedef std::function <double(const Individual&)> FitnessFunction;
	typedef std::vector<Individual*> Population;

	// Abstract Individual class
	class Individual{
	public:
		Individual(const CrossoverOperator crossover, const MutateOperator mutate) :
		 fitness(0.0), crossover(crossover), mutate(mutate), form(UNDEF) {}
		Individual(const Individual &c) {
			fitness = c.fitness;
			crossover = c.crossover;
			mutate = c.mutate;
			form = c.form;
		}
		virtual ~Individual(){}
		virtual Individual* clone() = 0;

	public:
		enum GenotypeForm {ARRAY, TREE, UNDEF};

		double fitness;
		CrossoverOperator crossover;
		MutateOperator mutate;
		GenotypeForm form;
	};

	// Abstract Individual class that has array genotype
	template <class T>
	class ArrayIndividual : public Individual{
	public:
		ArrayIndividual(const size_t gene_size, const CrossoverOperator crossover, const MutateOperator mutate) :
		 Individual(crossover, mutate), gene_size(gene_size) {
		 	this->form = ARRAY;
		 }
		ArrayIndividual(const ArrayIndividual &c) :
		 Individual(c)
		{
			this->gene_size = c.gene_size;
			this->genotype.resize(c.genotype.size());
			for(size_t i=0; i<c.genotype.size(); i++){
				this->genotype[i] = c.genotype[i];
			}
		}

	public:
		std::vector<T> genotype;
		size_t gene_size;
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