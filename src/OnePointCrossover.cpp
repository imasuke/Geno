// OnePointCrossover.cpp
#include "Geeni/Crossover.h"
#include "ArrayCrossover.h"

namespace Geeni{
	OnePointCrossover::OnePointCrossover(){
	}

	OnePointCrossover::~OnePointCrossover(){
	}

	void OnePointCrossover::operator()(Individual *ind1, Individual *ind2){
		//Geeni::onePointCrossover(&(ind1->genotype), &(ind2->genotype), ind1->genotype.size());
	}

	size_t OnePointCrossover::requiredParents(void){
		return kRequiredParents;
	}
}