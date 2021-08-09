// IntegerArrayIndividual.cpp
#include <vector>
#include <utility>
#include "Geno/IntegerArrayIndividual.h"
#include "Geno/util.h"

using std::vector;

namespace Geno{
	IntegerArrayIndividual::IntegerArrayIndividual(const size_t gene_size, const Initializer &init) :
	ArrayIndividual(gene_size)
	{
		this->gtype_ = INTEGER;	
		genotype.resize(gene_size);
		init(this);
	}

	IntegerArrayIndividual::IntegerArrayIndividual(const IntegerArrayIndividual &c) :
	ArrayIndividual(c)
	{
	}

	IntegerArrayIndividual::~IntegerArrayIndividual(){
		genotype.clear();
	}

	Individual* IntegerArrayIndividual::clone(){
		return new IntegerArrayIndividual(*this);
	}

	IntegerArrayIndividual::Initializer IntegerArrayIndividual::randomInitializer(const int value_min, const int value_max){
		return [value_min, value_max](IntegerArrayIndividual *ind){
			Randomizer rand;
			for(size_t i=0; i < ind->genotype.size(); i++){
				ind->genotype.at(i) = rand.randomInt(value_min, value_max);
			}
		};
	}

	IntegerArrayIndividual::Initializer IntegerArrayIndividual::uniqueInitializer(const int value_min, const int value_max){
		return [value_min, value_max](IntegerArrayIndividual *ind){
			vector<int> list(value_max-value_min+1);
			std::random_device rd;
			std::iota(list.begin(), list.end(), value_min);
			std::shuffle(list.begin(), list.end(), std::mt19937(rd()));

			auto it = list.begin();
			for(size_t i=0; i < ind->genotype.size(); i++){
				ind->genotype.at(i) = *it;
				if(it == list.end()){
					it = list.begin();
				}
				it++;
			}
		};
	}

	using Factory = IntegerArrayIndividual::Factory;
	using RandomMutation = IntegerArrayIndividual::RandomMutation;

	Factory::Factory():
	IndividualFactory(IntegerArrayIndividual::UniformCrossover(), IntegerArrayIndividual::RandomMutation(0, 10)),
	gene_size_(100),
	init_(IntegerArrayIndividual::randomInitializer(0, 10))
	{
	}

	Factory::~Factory(){
	}

	Individual* Factory::create(){
		return new IntegerArrayIndividual(gene_size_, init_);
	}

	Factory& Factory::geneSize(const size_t gene_size){
		gene_size_ = gene_size;
		return *this;
	}

	Factory& Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	RandomMutation::RandomMutation(const int value_min, const int value_max):
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
		IntegerArrayIndividual *iind = (IntegerArrayIndividual*)ind;

		for(size_t i=0; i<iind->genotype.size(); i++){
			iind->genotype[i] = rand.randomInt(value_min_, value_max_);
		}
	}

	RandomMutation* RandomMutation::clone(void){
		return new RandomMutation(*this);
	}
}
