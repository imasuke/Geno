// Individual.h
#ifndef INDIVIDUAL_HEADER
#define INDIVIDUAL_HEADER

#include <vector>
#include <functional>
#include "util/Tree.h"

namespace Geno{
	class Individual;
	using FitnessFunction = std::function <double(const Individual&)>;
	using Population = std::vector<Individual*>;

	// Abstract Individual class
	class Individual{
	public:
		enum GenotypeForm {ARRAY, TREE, FORM_UNDEF};
		enum GeneType {REAL, INTEGER, BINARY, MIX, TYPE_UNDEF};

		Individual() :
		 fitness(0.0), form_(FORM_UNDEF), gene_(TYPE_UNDEF) {}
		Individual(const GenotypeForm &form, const GeneType &gene):
		 fitness(0.0), form_(form), gene_(gene){}
		Individual(const Individual &c) {
			fitness = c.fitness;
			form_ = c.form_;
			gene_ = c.gene_;
		}
		virtual ~Individual(){}
		virtual Individual* clone() = 0;
		const GenotypeForm& genotype(){
			return form_;
		}
		const GeneType& genetype(){
			return gene_;
		}

	public:
		double fitness;
	protected:
		GenotypeForm form_;
		GeneType gene_;
	};

	// Abstract Individual class that has array genotype
	template <class T>
	class ArrayIndividual : public Individual{
	public:
		ArrayIndividual(const size_t gene_size) :
		 Individual(ARRAY, TYPE_UNDEF), gene_size(gene_size) {
		 }
		ArrayIndividual(const ArrayIndividual &c) :
		 Individual(c)
		{
			this->gene_size = c.gene_size;
			this->genotype.resize(c.genotype.size());
			for(size_t i=0; i<c.genotype.size(); i++){
				this->genotype[i] = c.genotype[i];
			}
		}
		virtual ~ArrayIndividual(){}

	public:
		std::vector<T> genotype;
		size_t gene_size;
	};

	// Abstract Individual class that has tree structure genotype
	template <class T>
	class TreeIndividual : public Individual{
	public:
		TreeIndividual(const unsigned int depth) :
		 Individual(TREE, TYPE_UNDEF), genotype(nullptr), depth(depth) {
		 }
		TreeIndividual(const TreeIndividual &c) :
		 Individual(c)
		{
			this->genotype = c.genotype;	
			this->depth = c.depth;
		}
		virtual ~TreeIndividual(){
			if(genotype != nullptr) delete genotype;
		}

	public:
		Tree<T> *genotype; // root node
		unsigned int depth;
	};
}

#endif