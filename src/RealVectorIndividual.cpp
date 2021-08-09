// RealVectorIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/RealVectorIndividual.h"
#include "Geno/util.h"

namespace Geno{
	RealVectorIndividual::RealVectorIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size)
	{
		this->gtype_ = REAL;	
		genotype.resize(gene_size);
		init(this);
	}

	RealVectorIndividual::RealVectorIndividual(const RealVectorIndividual &c) :
	ArrayIndividual(c)
	{
	}

	RealVectorIndividual::~RealVectorIndividual(){
		genotype.clear();
	}

	Individual* RealVectorIndividual::clone(){
		return new RealVectorIndividual(*this);
	}

	RealVectorIndividual::Initializer RealVectorIndividual::randomInitializer(const double value_min, const double value_max){
		return [value_min, value_max](RealVectorIndividual *ind){
			Randomizer rand;
			for(size_t i=0; i< ind->genotype.size(); i++){
				ind->genotype.at(i) = rand.randomDouble(value_min, value_max);
			}
		};
	}

	using Factory = RealVectorIndividual::Factory;
	using RandomMutation = RealVectorIndividual::RandomMutation;

	Factory::Factory() :
	IndividualFactory(RealVectorIndividual::BlxAlphaCrossover(0.3), RealVectorIndividual::RandomMutation(0.0, 1.0)),
	gene_size_(100),
	init_(RealVectorIndividual::randomInitializer(0.0, 1.0))
	{
	}

	Factory::~Factory(){
	}

	Individual* Factory::create(){
		return new RealVectorIndividual(gene_size_, init_);
	}

	Factory& Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	Factory& Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	RandomMutation::RandomMutation(const double value_min, const double value_max):
	value_min_(value_min), value_max_(value_max){
	}

	RandomMutation::RandomMutation(const RandomMutation &c)
	: Mutation(c){
		this->value_min_ = c.value_min_;
		this->value_max_ = c.value_max_;
	}

	RandomMutation::~RandomMutation(){
	}

	void RandomMutation::operator()(Individual *ind){
		Randomizer rand;
		RealVectorIndividual *rind = (RealVectorIndividual*)ind;
		for(size_t i=0; i<rind->genotype.size(); i++){
			rind->genotype[i] = rand.randomDouble(value_min_, value_max_);
		}
	}

	RandomMutation* RandomMutation::clone(void){
		return new RandomMutation(*this);
	}
}
