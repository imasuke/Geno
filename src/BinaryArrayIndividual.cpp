// BinaryArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geeni/BinaryArrayIndividual.h"
#include "Geeni/util.h"
#include "ArrayCrossover.h"

using std::vector;

namespace Geeni{
	BinaryArrayIndividual::BinaryArrayIndividual(const size_t gene_size, const Initializer &init, const CrossoverOperator &crossover, const MutateOperator &mutate) :
	ArrayIndividual(gene_size, crossover, mutate),
	init(init)
	{
		genotype.resize(gene_size);
		init(&genotype);
	}

	BinaryArrayIndividual::BinaryArrayIndividual(const BinaryArrayIndividual &c) :
	ArrayIndividual(c)
	{
		this->init = c.init;
	}

	BinaryArrayIndividual::~BinaryArrayIndividual(){
		genotype.clear();
	}

	Individual* BinaryArrayIndividual::clone(){
		return new BinaryArrayIndividual(*this);
	}

	BinaryArrayIndividual::Initializer BinaryArrayIndividual::randomInitializer(){
		return [](vector<bool> *gene){
			Randomizer rand;
			for(size_t i=0; i<gene->size(); i++){
				if(rand.randomDouble(1.0) > 0.5)
					gene->at(i) = true;
				else
					gene->at(i) = false;
			}
		};
	}

	CrossoverOperator BinaryArrayIndividual::onePointCrossover(){
		return OnePointCrossover<BinaryArrayIndividual>();
	}

	CrossoverOperator BinaryArrayIndividual::twoPointCrossover(){
		return TwoPointCrossover<BinaryArrayIndividual>();
	}

	CrossoverOperator BinaryArrayIndividual::uniformCrossover(){
		return UniformCrossover<BinaryArrayIndividual>();
	}

	MutateOperator BinaryArrayIndividual::randomMutate(){
		return [](Individual *ind){
			BinaryArrayIndividual *bind = (BinaryArrayIndividual*)ind;
			for(unsigned int i=0; i<bind->genotype.size(); i++){
				bind->genotype[i] = !bind->genotype[i];
			}
		};
	}

	BinaryArrayIndividual::Factory::Factory() :
	IndividualFactory(),
	gene_size_(100),
	init_(BinaryArrayIndividual::randomInitializer()),
	crossover_(BinaryArrayIndividual::uniformCrossover()),
	mutate_(BinaryArrayIndividual::randomMutate())
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
