// BinaryArrayIndividual.h
#ifndef BINARY_ARRAY_INDIVIDUAL_HEADER
#define BINARY_ARRAY_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"

namespace Geno{
	
	class BinaryArrayIndividual : public ArrayIndividual<bool>{
	public:
		typedef std::function <void(std::vector<bool>*)> Initializer;

		BinaryArrayIndividual(const size_t gene_size, const Initializer&);
		BinaryArrayIndividual(const BinaryArrayIndividual&);
		~BinaryArrayIndividual();
		Individual* clone();
		static Initializer randomInitializer();
		static Crossover* onePointCrossover();
		static Crossover* twoPointCrossover();
		static Crossover* uniformCrossover();
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

	public:
		Initializer init;
	};
}

#endif