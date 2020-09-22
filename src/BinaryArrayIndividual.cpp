// BinaryArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geeni/BinaryArrayIndividual.h"
#include "Geeni/util.h"
#include "ArrayCrossover.h"

namespace Geeni{
	BinaryArrayIndividual::BinaryArrayIndividual(const size_t gene_size, const Initializer &init, const CrossoverOperator &crossover, const MutateOperator &mutate) :
	Individual(crossover, mutate),
	gene_size(gene_size),
	init(init)
	{
		genotype.resize(gene_size);
		init(&genotype);
	}

	BinaryArrayIndividual::BinaryArrayIndividual(const BinaryArrayIndividual &c) :
	Individual(c)
	{
		this->gene_size = c.gene_size;
		this->init = c.init;
		this->genotype.resize(c.genotype.size());
		for(size_t i=0; i<c.genotype.size(); i++){
			this->genotype[i] = c.genotype[i];
		}
	}

	BinaryArrayIndividual::~BinaryArrayIndividual(){
		genotype.clear();
	}

	Individual* BinaryArrayIndividual::clone(){
		return new BinaryArrayIndividual(*this);
	}

	void BinaryArrayIndividual::randomInitializer(std::vector<bool> *gene){
		Randomizer rand;
		for(size_t i=0; i<gene->size(); i++){
			if(rand.randomDouble(1.0) > 0.5)
				gene->at(i) = true;
			else
				gene->at(i) = false;
		}
	}

	void BinaryArrayIndividual::onePointCrossover(Individual *ind1, Individual *ind2){
		BinaryArrayIndividual *bind1 = (BinaryArrayIndividual*)ind1;
		BinaryArrayIndividual *bind2 = (BinaryArrayIndividual*)ind2;
		Geeni::onePointCrossover(&(bind1->genotype), &(bind2->genotype), bind1->genotype.size());
	}

	void BinaryArrayIndividual::twoPointCrossover(Individual *ind1, Individual *ind2){
		BinaryArrayIndividual *bind1 = (BinaryArrayIndividual*)ind1;
		BinaryArrayIndividual *bind2 = (BinaryArrayIndividual*)ind2;
		Geeni::twoPointCrossover(&(bind1->genotype), &(bind2->genotype), bind1->genotype.size());
	}

	void BinaryArrayIndividual::uniformCrossover(Individual *ind1, Individual *ind2){
		BinaryArrayIndividual *bind1 = (BinaryArrayIndividual*)ind1;
		BinaryArrayIndividual *bind2 = (BinaryArrayIndividual*)ind2;
		Geeni::uniformCrossover(&(bind1->genotype), &(bind2->genotype), bind1->genotype.size());
	}

	void BinaryArrayIndividual::randomMutate(Individual *ind){
		BinaryArrayIndividual *bind = (BinaryArrayIndividual*)ind;
		for(unsigned int i=0; i<bind->genotype.size(); i++){
			bind->genotype[i] = !bind->genotype[i];
		}
	}

	BinaryArrayIndividual::Factory::Factory() :
	IndividualFactory(),
	gene_size_(100),
	init_(BinaryArrayIndividual::randomInitializer),
	crossover_(BinaryArrayIndividual::uniformCrossover),
	mutate_(BinaryArrayIndividual::randomMutate)
	{}

	BinaryArrayIndividual::Factory::~Factory(){
	}

	Individual* BinaryArrayIndividual::Factory::create(){
		return new BinaryArrayIndividual(gene_size_, init_, crossover_, mutate_);
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::crossover(const CrossoverOperator &crossover){
		crossover_ = crossover;
		return *this;
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::mutate(const MutateOperator &mutate){
		mutate_ = mutate;
		return *this;
	}

}
