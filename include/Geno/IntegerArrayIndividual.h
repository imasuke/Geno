// IntegerArrayIndividual.h
#ifndef INTEGER_ARRAY_INDIVIDUAL_HEADER
#define INTEGER_ARRAY_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"
#include "Geno/ArrayCrossover.h"
#include "Geno/ArrayMutation.h"

namespace Geno{
	
	class IntegerArrayIndividual : public ArrayIndividual<int>{
	public:
		using Initializer = std::function <void(IntegerArrayIndividual*)>;
		using OnePointCrossover = crossover::array::OnePointCrossover<IntegerArrayIndividual>;
		using TwoPointCrossover = crossover::array::TwoPointCrossover<IntegerArrayIndividual>;
		using UniformCrossover = crossover::array::UniformCrossover<IntegerArrayIndividual>;
		using CyclicCrossover = crossover::array::CyclicCrossover<IntegerArrayIndividual>;
		using PartiallyMappedCrossover = crossover::array::PartiallyMappedCrossover<IntegerArrayIndividual>;
		using OrderCrossover = crossover::array::OrderCrossover<IntegerArrayIndividual>;
		using SwapMutation = mutation::SwapMutation<IntegerArrayIndividual>;
		using ShuffleMutation = mutation::ShuffleMutation<IntegerArrayIndividual>;

		IntegerArrayIndividual(const size_t gene_size, const Initializer&);
		IntegerArrayIndividual(const IntegerArrayIndividual&);
		~IntegerArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer(const int value_min, const int value_max);
		static Initializer uniqueInitializer(const int value_min, const int value_max);

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

		class RandomMutation : public Mutation{
		public:
			RandomMutation(const int value_min, const int value_max);
			RandomMutation(const RandomMutation &c);
			~RandomMutation();
			void operator()(Individual *ind);
			RandomMutation* clone(void);
		private:
			int value_min_;
			int value_max_;
		};
	};
}

#endif