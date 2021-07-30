// Crossover.h
#ifndef CROSSOVER_HEADER
#define CROSSOVER_HEADER

#include "Geno/individual.h"

namespace Geno{
	class Crossover{
	public:
		Crossover(){}
		virtual ~Crossover(){}
		virtual void operator()(Individual *ind1, Individual *ind2) = 0;
		virtual size_t requiredParents(void) = 0;
	};
}

#endif