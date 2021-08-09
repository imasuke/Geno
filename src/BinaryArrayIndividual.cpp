// BinaryArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/BinaryArrayIndividual.h"
#include "Geno/util.h"
#include "Geno/ArrayCrossover.h"

using std::vector;

namespace Geno{
	BinaryArrayIndividual::BinaryArrayIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size)
	{
		this->gtype = BINARY;	
		genotype.resize(gene_size);
		init(this);
	}

	BinaryArrayIndividual::BinaryArrayIndividual(const BinaryArrayIndividual &c) :
	ArrayIndividual(c)
	{
	}

	BinaryArrayIndividual::~BinaryArrayIndividual(){
		genotype.clear();
	}

	Individual* BinaryArrayIndividual::clone(){
		return new BinaryArrayIndividual(*this);
	}

	BinaryArrayIndividual::Initializer BinaryArrayIndividual::randomInitializer(){
		return [](BinaryArrayIndividual *ind){
			Randomizer rand;
			for(size_t i=0; i< ind->genotype.size(); i++){
				if(rand.randomDouble(1.0) > 0.5)
					ind->genotype.at(i) = true;
				else
					ind->genotype.at(i) = false;
			}
		};
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
	IndividualFactory(BinaryArrayIndividual::UniformCrossover(), BinaryArrayIndividual::randomMutate()),
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
