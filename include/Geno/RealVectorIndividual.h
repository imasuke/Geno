// RealVectorIndividual.h
#ifndef REAL_VECTOR_INDIVIDUAL_HEADER
#define REAL_VECTOR_INDIVIDUAL_HEADER

#include "Geno/individual.h"

namespace Geno{
	
	class RealVectorIndividual : public ArrayIndividual<double>{
	public:
		typedef std::function <void(std::vector<double>*)> Initializer;

		RealVectorIndividual(const size_t gene_size, const Initializer&, const CrossoverOperator&, const MutateOperator&);
		RealVectorIndividual(const RealVectorIndividual&);
		~RealVectorIndividual();
		Individual* clone();
		static Initializer randomInitializer(const double value_min, const double value_max);
		static CrossoverOperator onePointCrossover();
		static CrossoverOperator twoPointCrossover();
		static CrossoverOperator uniformCrossover();
		static CrossoverOperator blxAlphaCrossover();
		static MutateOperator randomMutate(const double value_min, const double value_max);

		class Factory : public IndividualFactory{
		public:
			Factory();
			~Factory();
			Individual* create();
			Factory& geneSize(const size_t gene_size);
			Factory& initializer(const Initializer &init);
			Factory& crossover(const CrossoverOperator &crossover);
			Factory& mutate(const MutateOperator &mutate);

		private:
			size_t gene_size_;
			Initializer init_;
			CrossoverOperator crossover_;
			MutateOperator mutate_;
		};

	public:
		Initializer init;
	};
}

#endif