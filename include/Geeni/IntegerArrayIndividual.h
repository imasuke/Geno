// IntegerArrayIndividual.h
#ifndef INTEGER_ARRAY_INDIVIDUAL_HEADER
#define INTEGER_ARRAY_INDIVIDUAL_HEADER

#include "Geeni/individual.h"

namespace Geeni{
	
	class IntegerArrayIndividual : public Individual{
	public:
		typedef std::function <void(std::vector<int>*)> Initializer;

		IntegerArrayIndividual(const size_t gene_size, const Initializer&, const CrossoverOperator&, const MutateOperator&);
		IntegerArrayIndividual(const IntegerArrayIndividual&);
		~IntegerArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer(const int value_min, const int value_max);
		static Initializer uniqueInitializer(const int value_min, const int value_max);
		static void onePointCrossover(Individual *ind1, Individual *ind2);
		static void twoPointCrossover(Individual *ind1, Individual *ind2);
		static void uniformCrossover(Individual *ind1, Individual *ind2);
		static void cyclicCrossover(Individual *ind1, Individual *ind2);
		static void partiallyMappedCrossover(Individual *ind1, Individual *ind2);
		static void orderCrossover(Individual *ind1, Individual *ind2);
		static void randomMutate(Individual *ind);
		static MutateOperator randomMutate(const int value_min, const int value_max);
		static void swapMutate(Individual *ind);
		static void shuffleMutate(Individual *ind);

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
		std::vector<int> genotype;
		size_t gene_size;
		Initializer init;
	};
}

#endif