// RealVectorIndividual.h
#ifndef REAL_VECTOR_INDIVIDUAL_HEADER
#define REAL_VECTOR_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"

namespace Geno{
	
	class RealVectorIndividual : public ArrayIndividual<double>{
	public:
		typedef std::function <void(std::vector<double>*)> Initializer;

		RealVectorIndividual(const size_t gene_size, const Initializer&);
		RealVectorIndividual(const RealVectorIndividual&);
		~RealVectorIndividual();
		Individual* clone();
		static Initializer randomInitializer(const double value_min, const double value_max);
		static Crossover* onePointCrossover();
		static Crossover* twoPointCrossover();
		static Crossover* uniformCrossover();
		static Crossover* blxAlphaCrossover(const double alpha);
		static MutateOperator randomMutate(const double value_min, const double value_max);

		class Factory : public IndividualFactory{
		public:
			Factory();
			~Factory();
			Individual* create();
			Factory& geneSize(const size_t gene_size);
			Factory& initializer(const Initializer &init);

		private:
			size_t gene_size_;
			Initializer init_;
		};

	public:
		Initializer init;
	};
}

#endif