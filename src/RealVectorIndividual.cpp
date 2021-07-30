// RealVectorIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/RealVectorIndividual.h"
#include "Geno/util.h"
#include "ArrayCrossover.h"

namespace Geno{
	RealVectorIndividual::RealVectorIndividual(const size_t gene_size, const Initializer &init, const CrossoverOperator &crossover, const MutateOperator &mutate) :
	ArrayIndividual(gene_size, crossover, mutate),
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

	CrossoverOperator RealVectorIndividual::onePointCrossover(){
		return OnePointCrossover<RealVectorIndividual>();
	}

	CrossoverOperator RealVectorIndividual::twoPointCrossover(){
		return TwoPointCrossover<RealVectorIndividual>();
	}

	CrossoverOperator RealVectorIndividual::uniformCrossover(){
		return UniformCrossover<RealVectorIndividual>();
	}

	CrossoverOperator RealVectorIndividual::blxAlphaCrossover(){
		return [](Individual *ind1, Individual *ind2){
			RealVectorIndividual *rind1, *rind2;
			Randomizer rand;
			double alpha = 0.3, vmax, vmin, vdiff;
			unsigned int n;

			rind1 = (RealVectorIndividual*)ind1;
			rind2 = (RealVectorIndividual*)ind2;
			n = rind1->genotype.size();

			for(size_t i=0; i<n; i++){
				vmin = std::min(rind1->genotype[i], rind2->genotype[i]);
				vmax = std::max(rind1->genotype[i], rind2->genotype[i]);
				vdiff = std::abs(rind1->genotype[i] - rind2->genotype[i]);
				rind1->genotype[i] = rand.randomDouble(vmin - alpha * vdiff, vmax + alpha * vdiff);
				rind2->genotype[i] = rand.randomDouble(vmin - alpha * vdiff, vmax + alpha * vdiff);
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
	gene_size_(100),
	init_(RealVectorIndividual::randomInitializer(0.0, 1.0)),
	crossover_(RealVectorIndividual::blxAlphaCrossover()), 
	mutate_(RealVectorIndividual::randomMutate(0.0, 1.0))
	{
	}

	RealVectorIndividual::Factory::~Factory(){
	}

	Individual* RealVectorIndividual::Factory::create(){
		return new RealVectorIndividual(gene_size_, init_, crossover_, mutate_);
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::crossover(const CrossoverOperator &crossover){
		crossover_ = crossover;
		return *this;
	}

	RealVectorIndividual::Factory& RealVectorIndividual::Factory::mutate(const MutateOperator &mutate){
		mutate_ = mutate;
		return *this;
	}

}
