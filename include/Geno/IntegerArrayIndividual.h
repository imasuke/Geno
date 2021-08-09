// IntegerArrayIndividual.h
#ifndef INTEGER_ARRAY_INDIVIDUAL_HEADER
#define INTEGER_ARRAY_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"
#include "Geno/ArrayCrossover.h"

namespace Geno{
	
	class IntegerArrayIndividual : public ArrayIndividual<int>{
	public:
		using Initializer = std::function <void(IntegerArrayIndividual*)>;
		using OnePointCrossover = crossover::OnePointCrossover<IntegerArrayIndividual>;
		using TwoPointCrossover = crossover::TwoPointCrossover<IntegerArrayIndividual>;
		using UniformCrossover = crossover::UniformCrossover<IntegerArrayIndividual>;
		using CyclicCrossover = crossover::CyclicCrossover<IntegerArrayIndividual>;
		using PartiallyMappedCrossover = crossover::PartiallyMappedCrossover<IntegerArrayIndividual>;
		using OrderCrossover = crossover::OrderCrossover<IntegerArrayIndividual>;

		IntegerArrayIndividual(const size_t gene_size, const Initializer&);
		IntegerArrayIndividual(const IntegerArrayIndividual&);
		~IntegerArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer(const int value_min, const int value_max);
		static Initializer uniqueInitializer(const int value_min, const int value_max);
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
	};
}

#endif