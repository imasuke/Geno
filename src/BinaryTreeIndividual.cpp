// BinaryTreeIndividual.cpp
#include <utility>
#include <functional>
#include "Geno/BinaryTreeIndividual.h"
#include "Geno/util.h"

namespace Geno{
	BinaryTreeIndividual::BinaryTreeIndividual(const unsigned int depth, const Initializer &init) :
	TreeIndividual(depth)
	{
		this->gene_ = BINARY;	
		init(this);
	}

	BinaryTreeIndividual::BinaryTreeIndividual(const BinaryTreeIndividual &c) :
	TreeIndividual(c)
	{
	}

	BinaryTreeIndividual::~BinaryTreeIndividual(){
	}

	Individual* BinaryTreeIndividual::clone(){
		return new BinaryTreeIndividual(*this);
	}

	BinaryTreeIndividual::Initializer BinaryTreeIndividual::randomInitializer(){
		return [](BinaryTreeIndividual *ind){
			generateRandomGenotype(ind->genotype, ind->depth);
		};
	}

	void BinaryTreeIndividual::generateRandomGenotype(Tree<bool> *genotype, const unsigned int max_depth){
		std::function<void(Tree<bool>*, const unsigned int)> init_node = [&init_node, max_depth](Tree<bool> *n, const unsigned int depth){
			Randomizer rand;
			// Stop initialize if current depth exceeds the max depth
            if(depth > max_depth) return;
            // Initilize the sub nodes randomly
            n->right = (rand.randomDouble(1.0) > 0.5) ? new Tree<bool>(rand.randomBool()) : nullptr;
            n->left = (rand.randomDouble(1.0) > 0.5) ? new Tree<bool>(rand.randomBool()) : nullptr;
            // Next depth
            if(n->right != nullptr) init_node(n->right, depth+1);
            if(n->left != nullptr) init_node(n->left, depth+1);
        };
        init_node(genotype, 1); // Start init from root node, depth = 1
	}

	using Factory = BinaryTreeIndividual::Factory;
	using RandomMutation = BinaryTreeIndividual::RandomMutation;

	Factory::Factory() :
	IndividualFactory(BinaryTreeIndividual::OnePointCrossover(), BinaryTreeIndividual::RandomMutation()),
	depth_(5),
	init_(BinaryTreeIndividual::randomInitializer())
	{}

	Factory::~Factory(){
	}

	Individual* Factory::create(){
		return new BinaryTreeIndividual(depth_, init_);
	}

	Factory& Factory::depth(const unsigned int depth){
		depth_ = depth;
		return *this;
	}

	Factory& Factory::initializer(const Initializer &init){
		init_ = init;
		return *this;
	}

	RandomMutation::RandomMutation(){
	}

	RandomMutation::RandomMutation(const RandomMutation &c)
	: Mutation(c){
	}

	RandomMutation::~RandomMutation(){
	}

	void RandomMutation::operator()(Individual *ind){
		BinaryTreeIndividual *bind = (BinaryTreeIndividual*)ind;
		Tree<bool> *n = randomSubNode(bind->genotype);
		BinaryTreeIndividual::generateRandomGenotype(n, bind->depth);
	}

	RandomMutation* RandomMutation::clone(void){
		return new RandomMutation(*this);
	}
}
