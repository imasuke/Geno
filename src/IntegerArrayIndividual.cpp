// IntegerArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geeni/IntegerArrayIndividual.h"
#include "Geeni/util.h"
#include "ArrayCrossover.h"

using std::vector;

namespace Geeni{
	IntegerArrayIndividual::IntegerArrayIndividual(const size_t gene_size, const Initializer &init, const CrossoverOperator &crossover, const MutateOperator &mutate) :
	ArrayIndividual(gene_size, crossover, mutate),
	init(init)
	{
		genotype.resize(gene_size);
		init(&genotype);
	}

	IntegerArrayIndividual::IntegerArrayIndividual(const IntegerArrayIndividual &c) :
	ArrayIndividual(c)
	{
		this->init = c.init;
	}

	IntegerArrayIndividual::~IntegerArrayIndividual(){
		genotype.clear();
	}

	Individual* IntegerArrayIndividual::clone(){
		return new IntegerArrayIndividual(*this);
	}

	IntegerArrayIndividual::Initializer IntegerArrayIndividual::randomInitializer(const int value_min, const int value_max){
		return [value_min, value_max](vector<int> *genotype){
			Randomizer rand;
			for(size_t i=0; i<genotype->size(); i++){
				genotype->at(i) = rand.randomInt(value_min, value_max);
			}
		};
	}

	IntegerArrayIndividual::Initializer IntegerArrayIndividual::uniqueInitializer(const int value_min, const int value_max){
		return [value_min, value_max](vector<int> *genotype){
			vector<int> list(value_max-value_min+1);
			std::random_device rd;
			std::iota(list.begin(), list.end(), value_min);
			std::shuffle(list.begin(), list.end(), std::mt19937(rd()));

			auto it = list.begin();
			for(size_t i=0; i<genotype->size(); i++){
				genotype->at(i) = *it;
				if(it == list.end()){
					it = list.begin();
				}
				it++;
			}
		};
	}

	CrossoverOperator IntegerArrayIndividual::onePointCrossover(){
		return OnePointCrossover<IntegerArrayIndividual>();
	}

	CrossoverOperator IntegerArrayIndividual::twoPointCrossover(){
		return TwoPointCrossover<IntegerArrayIndividual>();
	}

	CrossoverOperator IntegerArrayIndividual::uniformCrossover(){
		return UniformCrossover<IntegerArrayIndividual>();
	}

	CrossoverOperator IntegerArrayIndividual::cyclicCrossover(){
		return [](Individual *ind1, Individual *ind2){
			IntegerArrayIndividual *iind1 = (IntegerArrayIndividual*)ind1;
			IntegerArrayIndividual *iind2 = (IntegerArrayIndividual*)ind2;
			Geeni::cyclicCrossover(&(iind1->genotype), &(iind2->genotype), iind1->genotype.size());
		};
	}

	CrossoverOperator IntegerArrayIndividual::partiallyMappedCrossover(){
		return [](Individual *ind1, Individual *ind2){
			IntegerArrayIndividual *iind1 = (IntegerArrayIndividual*)ind1;
			IntegerArrayIndividual *iind2 = (IntegerArrayIndividual*)ind2;
			Geeni::partiallyMappedCrossover(&(iind1->genotype), &(iind2->genotype), iind1->genotype.size());
		};
	}

	CrossoverOperator IntegerArrayIndividual::orderCrossover(){
		return [](Individual *ind1, Individual *ind2){
			IntegerArrayIndividual *iind1 = (IntegerArrayIndividual*)ind1;
			IntegerArrayIndividual *iind2 = (IntegerArrayIndividual*)ind2;
			Geeni::orderCrossover(&(iind1->genotype), &(iind2->genotype), iind1->genotype.size());
		};
	}

	MutateOperator IntegerArrayIndividual::randomMutate(const int value_min, const int value_max){
		return [value_min, value_max](Individual *ind){
			Randomizer rand;
			IntegerArrayIndividual *iind = (IntegerArrayIndividual*)ind;

			for(size_t i=0; i<iind->genotype.size(); i++){
				iind->genotype[i] = rand.randomInt(value_min, value_max);
			}
		};
	}

	MutateOperator IntegerArrayIndividual::swapMutate(){
		return [](Individual *ind){
			Randomizer rand;
			IntegerArrayIndividual *iind = (IntegerArrayIndividual*)ind;
			unsigned int gene_size = iind->genotype.size();
			std::swap(iind->genotype.at(rand.randomInt(gene_size-1)), iind->genotype.at(rand.randomInt(gene_size-1)));
		};
	}

	MutateOperator IntegerArrayIndividual::shuffleMutate(){
		return [](Individual *ind){
			Randomizer rand;
			IntegerArrayIndividual *iind = (IntegerArrayIndividual*)ind;	
			std::random_device rd;
			unsigned int rindex1, rindex2;

			rindex1 = rand.randomInt(iind->genotype.size()-1);
			rindex2 = rand.randomInt(iind->genotype.size()-1);
			if(rindex1 > rindex2) std::swap(rindex1, rindex2);
			std::shuffle(iind->genotype.begin()+rindex1 , iind->genotype.begin()+rindex2, std::mt19937(rd()));
		};
	}

	IntegerArrayIndividual::Factory::Factory():
	IndividualFactory(),
	gene_size_(100),
	init_(IntegerArrayIndividual::randomInitializer(0, 10)),
	crossover_(IntegerArrayIndividual::uniformCrossover()),
	mutate_(IntegerArrayIndividual::randomMutate(0, 10))
	{
	}

	IntegerArrayIndividual::Factory::~Factory(){
	}

	Individual* IntegerArrayIndividual::Factory::create(){
		return new IntegerArrayIndividual(gene_size_, init_, crossover_, mutate_);
	}

	IntegerArrayIndividual::Factory& IntegerArrayIndividual::Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	IntegerArrayIndividual::Factory& IntegerArrayIndividual::Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	IntegerArrayIndividual::Factory& IntegerArrayIndividual::Factory::crossover(const CrossoverOperator &crossover){
		crossover_ = crossover;
		return *this;
	}

	IntegerArrayIndividual::Factory& IntegerArrayIndividual::Factory::mutate(const MutateOperator &mutate){
		mutate_ = mutate;
		return *this;
	}
}
