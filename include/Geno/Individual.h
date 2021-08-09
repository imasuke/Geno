// Individual.h
#ifndef INDIVIDUAL_HEADER
#define INDIVIDUAL_HEADER

#include <vector>
#include <functional>

namespace Geno{
	class Individual;
	typedef std::function <double(const Individual&)> FitnessFunction;
	typedef std::vector<Individual*> Population;

	// Abstract Individual class
	class Individual{
	public:
		enum GenotypeForm {ARRAY, TREE, FORM_UNDEF};
		enum GeneType {REAL, INTEGER, BINARY, MIX, TYPE_UNDEF};

		Individual() :
		 fitness(0.0), form_(FORM_UNDEF), gtype_(TYPE_UNDEF) {}
		Individual(const GenotypeForm &form, const GeneType &gtype):
		 fitness(0.0), form_(form), gtype_(gtype){}
		Individual(const Individual &c) {
			fitness = c.fitness;
			form_ = c.form_;
			gtype_ = c.gtype_;
		}
		virtual ~Individual(){}
		virtual Individual* clone() = 0;
		const GenotypeForm& genotypeForm(){
			return form_;
		}
		const GeneType& genotype(){
			return gtype_;
		}

	public:
		double fitness;
	protected:
		GenotypeForm form_;
		GeneType gtype_;
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

	public:
		std::vector<T> genotype;
		size_t gene_size;
	};
}

#endif