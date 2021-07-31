// BinaryArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/BinaryArrayIndividual.h"
#include "Geno/util.h"
#include "Geno/ArrayCrossover.h"

using std::vector;

namespace Geno{
	BinaryArrayIndividual::BinaryArrayIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size),
	init(init)
	{
		this->gtype = BINARY;	
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

	Crossover* BinaryArrayIndividual::onePointCrossover(){
		return new OnePointCrossover<BinaryArrayIndividual>();
	}

	Crossover* BinaryArrayIndividual::twoPointCrossover(){
		return new TwoPointCrossover<BinaryArrayIndividual>();
	}

	Crossover* BinaryArrayIndividual::uniformCrossover(){
		return new UniformCrossover<BinaryArrayIndividual>();
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
	IndividualFactory(BinaryArrayIndividual::uniformCrossover(), BinaryArrayIndividual::randomMutate()),
	gene_size_(100),
	init_(BinaryArrayIndividual::randomInitializer())
	{}

	BinaryArrayIndividual::Factory::~Factory(){
	}

	Individual* BinaryArrayIndividual::Factory::create(){
		return new BinaryArrayIndividual(gene_size_, init_);
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	BinaryArrayIndividual::Factory& BinaryArrayIndividual::Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}
}
