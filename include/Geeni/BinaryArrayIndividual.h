// BinaryArrayIndividual.h
#ifndef BINARY_ARRAY_INDIVIDUAL_HEADER
#define BINARY_ARRAY_INDIVIDUAL_HEADER

#include "Geeni/individual.h"

namespace Geeni{
	
	class BinaryArrayIndividual : public Individual{
	public:
		typedef std::function <void(std::vector<bool>*)> Initializer;

		BinaryArrayIndividual(const size_t gene_size, const Initializer&, const CrossoverOperator&, const MutateOperator&);
		BinaryArrayIndividual(const BinaryArrayIndividual&);
		~BinaryArrayIndividual();
		Individual* clone();
		static void randomInitializer(std::vector<bool> *gene);
		static void onePointCrossover(Individual *ind1, Individual *ind2);
		static void twoPointCrossover(Individual *ind1, Individual *ind2);
		static void uniformCrossover(Individual *ind1, Individual *ind2);
		static void randomMutate(Individual *ind);

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
		std::vector<bool> genotype;
		size_t gene_size;
		Initializer init;
	};
}

#endif