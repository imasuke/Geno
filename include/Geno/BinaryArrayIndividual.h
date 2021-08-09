// BinaryArrayIndividual.h
#ifndef BINARY_ARRAY_INDIVIDUAL_HEADER
#define BINARY_ARRAY_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"
#include "Geno/ArrayCrossover.h"

namespace Geno{
	
	class BinaryArrayIndividual : public ArrayIndividual<bool>{
	public:
		using Initializer = std::function <void(BinaryArrayIndividual*)>;
		using OnePointCrossover = crossover::OnePointCrossover<BinaryArrayIndividual>;
		using TwoPointCrossover = crossover::TwoPointCrossover<BinaryArrayIndividual>;
		using UniformCrossover = crossover::UniformCrossover<BinaryArrayIndividual>;

		BinaryArrayIndividual(const size_t gene_size, const Initializer&);
		BinaryArrayIndividual(const BinaryArrayIndividual&);
		~BinaryArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer();
		static MutateOperator randomMutate();

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