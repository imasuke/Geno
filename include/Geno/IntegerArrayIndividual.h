// IntegerArrayIndividual.h
#ifndef INTEGER_ARRAY_INDIVIDUAL_HEADER
#define INTEGER_ARRAY_INDIVIDUAL_HEADER

#include "Geno/individual.h"

namespace Geno{
	
	class IntegerArrayIndividual : public ArrayIndividual<int>{
	public:
		typedef std::function <void(std::vector<int>*)> Initializer;

		IntegerArrayIndividual(const size_t gene_size, const Initializer&);
		IntegerArrayIndividual(const IntegerArrayIndividual&);
		~IntegerArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer(const int value_min, const int value_max);
		static Initializer uniqueInitializer(const int value_min, const int value_max);
		static CrossoverOperator onePointCrossover();
		static CrossoverOperator twoPointCrossover();
		static CrossoverOperator uniformCrossover();
		static CrossoverOperator cyclicCrossover();
		static CrossoverOperator partiallyMappedCrossover();
		static CrossoverOperator orderCrossover();
		static MutateOperator randomMutate();
		static MutateOperator randomMutate(const int value_min, const int value_max);
		static MutateOperator swapMutate();
		static MutateOperator shuffleMutate();

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