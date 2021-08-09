// AlternationModel.cpp
#include "Geno/AlternationModel.h"
#include "Geno/util.h"

using std::vector;

namespace Geno{
	void AlternationModel::mutateChildren(double mutation_rate){
		Randomizer rand;
		for(unsigned int i=0; i<children_.size(); i++){
			if(rand.randomDouble(1.0) < mutation_rate){
				(*ops_.mutate)(children_[i]);
			}
		}	
	}

	void AlternationModel::evaluateChildren(){
		for(unsigned int i=0; i<children_.size(); i++){
			children_[i]->fitness = ops_.ff(*children_[i]);
		}
	}
}