// AlternationModel.cpp
#include "Geeni/AlternationModel.h"
#include "Geeni/util.h"

using std::vector;

namespace Geeni{
	void AlternationModel::mutateChildren(double mutation_rate){
		Randomizer rand;
		for(unsigned int i=0; i<children_.size(); i++){
			if(rand.randomDouble(1.0) < mutation_rate){
				children_[i]->mutate(children_[i]);
			}
		}	
	}

	void AlternationModel::evaluateChildren(const FitnessFunction &ff){
		for(unsigned int i=0; i<children_.size(); i++){
			children_[i]->fitness = ff(*children_[i]);
		}
	}
}