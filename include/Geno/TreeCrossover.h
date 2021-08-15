// TreeCrossover.h
#ifndef TREE_CROSSOVER_HEADER
#define TREE_CROSSOVER_HEADER

#include <utility>
#include <algorithm>
#include "Geno/Individual.h"
#include "Geno/util.h"
#include "Crossover.h"

namespace Geno::crossover::tree{
	template <class T>
	void onePointCrossover(Tree<T> *ind1, Tree<T> *ind2) {
		Tree<T> *cross_point_ind1 = randomSubNode(ind1);
		Tree<T> *cross_point_ind2 = randomSubNode(ind2);
		Tree<T> tmp;

		tmp = *cross_point_ind1;
		*cross_point_ind1 = *cross_point_ind2;
		*cross_point_ind2 = tmp;
	}

	template <class T>
	void twoPointCrossover(Tree<T> *ind1, Tree<T> *ind2){
		Tree<T> *cross_point1_ind1 = randomSubNode(ind1);
		Tree<T> *cross_point2_ind1 = randomSubNode(ind1);
		Tree<T> *cross_point1_ind2 = randomSubNode(ind2);
		Tree<T> *cross_point2_ind2 = randomSubNode(ind2);
		Tree<T> tmp;

		// Cross point 1
		tmp = *cross_point1_ind1;
		*cross_point1_ind1 = *cross_point1_ind2;
		*cross_point1_ind2 = tmp;
		// Cross point 2
		tmp = *cross_point2_ind1;
		*cross_point2_ind1 = *cross_point2_ind2;
		*cross_point2_ind2 = tmp;
	}

	// Crossover template class
	template <class T>
	class OnePointCrossover : public Crossover2p{
	public:
		OnePointCrossover(){
			requiredParents_ = 2;
		}
		OnePointCrossover(const OnePointCrossover &c) : Crossover2p(c){
		}
		~OnePointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->genotype() == Individual::TREE && ind2->genotype() == Individual::TREE){
				T *tree_ind1 = static_cast<T*>(ind1);
				T *tree_ind2 = static_cast<T*>(ind2);
				onePointCrossover(tree_ind1->genotype, tree_ind2->genotype);
			}
		}
		OnePointCrossover* clone(void){
			return new OnePointCrossover(*this);
		}
	};

	template <class T>
	class TwoPointCrossover : public Crossover2p{
	public:
		TwoPointCrossover(){
			requiredParents_ = 2;
		}
		TwoPointCrossover(const TwoPointCrossover &c) : Crossover2p(c){
		}
		~TwoPointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->genotype() == Individual::TREE && ind2->genotype() == Individual::TREE){
				T *tree_ind1 = static_cast<T*>(ind1);
				T *tree_ind2 = static_cast<T*>(ind2);
				twoPointCrossover(tree_ind1->genotype, tree_ind2->genotype);
			}
		}
		TwoPointCrossover* clone(void){
			return new TwoPointCrossover(*this);
		}
	};
}

#endif