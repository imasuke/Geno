// BinaryArrayIndividual.h
#ifndef BINARY_ARRAY_TREE_HEADER
#define BINARY_ARRAY_TREE_HEADER

#include "Geno/IndividualFactory.h"
#include "Geno/TreeCrossover.h"

namespace Geno{
	
	class BinaryTreeIndividual : public TreeIndividual<bool>{
	public:
		using Initializer = std::function <void(BinaryTreeIndividual*)>;
		using OnePointCrossover = crossover::tree::OnePointCrossover<BinaryTreeIndividual>;
		using TwoPointCrossover = crossover::tree::TwoPointCrossover<BinaryTreeIndividual>;

		BinaryTreeIndividual(const unsigned int depth, const Initializer&);
		BinaryTreeIndividual(const BinaryTreeIndividual&);
		~BinaryTreeIndividual();
		Individual* clone();
		static Initializer randomInitializer();
		static void generateRandomGenotype(Tree<bool> *genotype, const unsigned int max_depth);

		class Factory : public IndividualFactory{
		public:
			Factory();
			~Factory();
			Individual* create();
			Factory& depth(const unsigned int depth);
			Factory& initializer(const Initializer &init);

		private:
			unsigned int depth_;
			Initializer init_;
		};

		class RandomMutation : public Mutation{
		public:
			RandomMutation();
			RandomMutation(const RandomMutation &c);
			~RandomMutation();
			void operator()(Individual *ind);
			RandomMutation* clone(void);
		};
	};
}

#endif