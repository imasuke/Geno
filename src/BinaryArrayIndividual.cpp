// BinaryArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/BinaryArrayIndividual.h"
#include "Geno/util.h"

using std::vector;

namespace Geno{
	BinaryArrayIndividual::BinaryArrayIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size)
	{
		this->gtype_ = BINARY;	
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

	using Factory = BinaryArrayIndividual::Factory;
	using RandomMutation = BinaryArrayIndividual::RandomMutation;

	Factory::Factory() :
	IndividualFactory(BinaryArrayIndividual::UniformCrossover(), BinaryArrayIndividual::RandomMutation()),
	gene_size_(100),
	init_(BinaryArrayIndividual::randomInitializer())
	{}

	Factory::~Factory(){
	}

	Individual* Factory::create(){
		return new BinaryArrayIndividual(gene_size_, init_);
	}

	Factory& Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	Factory& Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	RandomMutation::RandomMutation(){
	}

	RandomMutation::RandomMutation(const RandomMutation &c)
	: Mutation(c){
	}

	RandomMutation::~RandomMutation(){
	}

	void RandomMutation::operator()(Individual *ind){
		BinaryArrayIndividual *bind = (BinaryArrayIndividual*)ind;
		for(unsigned int i=0; i<bind->genotype.size(); i++){
			bind->genotype[i] = !bind->genotype[i];
		}
	}

	RandomMutation* RandomMutation::clone(void){
		return new RandomMutation(*this);
	}
}
