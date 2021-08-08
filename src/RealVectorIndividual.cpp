// RealVectorIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/RealVectorIndividual.h"
#include "Geno/util.h"
#include "Geno/ArrayCrossover.h"

namespace Geno{
	RealVectorIndividual::RealVectorIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size),
	init(init)
	{
		this->gtype = REAL;	
		genotype.resize(gene_size);
		init(&genotype);
	}

	RealVectorIndividual::RealVectorIndividual(const RealVectorIndividual &c) :
	ArrayIndividual(c)
	{
		this->init = c.init;
	}

	RealVectorIndividual::~RealVectorIndividual(){
		genotype.clear();
	}

	Individual* RealVectorIndividual::clone(){
		return new RealVectorIndividual(*this);
	}

	RealVectorIndividual::Initializer RealVectorIndividual::randomInitializer(const double value_min, const double value_max){
		return [value_min, value_max](std::vector<double> *genotype){
			Randomizer rand;
			for(size_t i=0; i<genotype->size(); i++){
				genotype->at(i) = rand.randomDouble(value_min, value_max);
			}
		};
	}


	MutateOperator RealVectorIndividual::randomMutate(const double value_min, const double value_max){
		return [value_min, value_max](Individual *ind){
			Randomizer rand;
			RealVectorIndividual *rind = (RealVectorIndividual*)ind;
			for(size_t i=0; i<rind->genotype.size(); i++){
				rind->genotype[i] = rand.randomDouble(value_min, value_max);
			}
		};
	}

	RealVectorIndividual::Factory::Factory() :
	IndividualFactory(RealVectorIndividual::BlxAlphaCrossover(0.3), RealVectorIndividual::randomMutate(0.0, 1.0)),
	gene_size_(100),
	init_(RealVectorIndividual::randomInitializer(0.0, 1.0))
	{
	}

	RealVectorIndividual::Factory::~Factory(){
	}

	Individual* RealVectorIndividual::Factory::create(){
		return new RealVectorIndividual(gene_size_, init_);
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

}
