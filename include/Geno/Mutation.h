// Mutation.h
#ifndef MUTATION_HEADER 
#define MUTATION_HEADER 

#include "Geno/individual.h"

namespace Geno{
	class Mutation{
	public:
		Mutation(){}
		Mutation(const Mutation &c){}
		virtual ~Mutation(){}
		virtual void operator()(Individual *ind) = 0;
		virtual Mutation* clone(void) = 0;
	};
}

#endif