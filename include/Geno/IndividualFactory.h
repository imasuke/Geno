// IndividualFactory.h
#ifndef INDIVIDUAL_FACTORY_HEADER
#define INDIVIDUAL_FACTORY_HEADER

#include "Individual.h"
#include "Crossover.h"
#include "Mutation.h"

namespace Geno{
	// Abstract Factory class
	class IndividualFactory{
	public:
		IndividualFactory(){}
		IndividualFactory(Crossover *crossover, Mutation *mutate) : crossover_(crossover), mutate_(mutate){
		}
		IndividualFactory(Crossover &&crossover, Mutation &&mutate) : crossover_(crossover.clone()), mutate_(mutate.clone()){
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
		IndividualFactory& mutate(Mutation *mutate){
			mutate_ = mutate;
			return *this;
		}
		IndividualFactory& mutate(Mutation &&mutate){
			mutate_ = mutate.clone();
			return *this;
		}
		Mutation* mutate(){
			return mutate_;
		}
	private:
		Crossover *crossover_;
		Mutation *mutate_;
	};
}

#endif