// Individual.h
#ifndef INDIVIDUAL_HEADER
#define INDIVIDUAL_HEADER

#include <vector>
#include <functional>

namespace Geno{
	class Individual;
	typedef std::function <void(Individual*)> MutateOperator;
	typedef std::function <double(const Individual&)> FitnessFunction;
	typedef std::vector<Individual*> Population;

	// Abstract Individual class
	class Individual{
	public:
		Individual() :
		 fitness(0.0), form(FORM_UNDEF), gtype(TYPE_UNDEF) {}
		Individual(const Individual &c) {
			fitness = c.fitness;
			form = c.form;
			gtype = c.gtype;
		}
		virtual ~Individual(){}
		virtual Individual* clone() = 0;

	public:
		enum GenotypeForm {ARRAY, TREE, FORM_UNDEF};
		enum GeneType {REAL, INTEGER, BINARY, MIX, TYPE_UNDEF};

		double fitness;
		GenotypeForm form;
		GeneType gtype;
	};

	// Abstract Individual class that has array genotype
	template <class T>
	class ArrayIndividual : public Individual{
	public:
		ArrayIndividual(const size_t gene_size) :
		 Individual(), gene_size(gene_size) {
		 	this->form = ARRAY;
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

	public:
		std::vector<T> genotype;
		size_t gene_size;
	};
}

#endif