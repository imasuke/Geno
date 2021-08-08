// IndividualFactory.h
#ifndef INDIVIDUAL_FACTORY_HEADER
#define INDIVIDUAL_FACTORY_HEADER

#include "Individual.h"
#include "Crossover.h"

namespace Geno{
	// Abstract Factory class
	class IndividualFactory{
	public:
		IndividualFactory(){}
		IndividualFactory(Crossover *crossover, const MutateOperator &mutate) : crossover_(crossover), mutate_(mutate){
		}
		IndividualFactory(Crossover &&crossover, const MutateOperator &mutate) : crossover_(crossover.clone()), mutate_(mutate){
		}
		virtual ~IndividualFactory(){}
		virtual Individual* create() = 0; 
		IndividualFactory& crossover(Crossover *crossover){
			crossover_ = crossover;
			return *this;
		}
		IndividualFactory& crossover(Crossover &&crossover){
			crossover_ = crossover.clone();
			return *this;
		}
		Crossover* crossover(){
			return crossover_;
		}
		IndividualFactory& mutate(const MutateOperator &mutate){
			mutate_ = mutate;
			return *this;
		}
		MutateOperator mutate(){
			return mutate_;
		}
	private:
		Crossover *crossover_;
		MutateOperator mutate_;
	};
}

#endif