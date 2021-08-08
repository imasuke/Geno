// Crossover.h
#ifndef CROSSOVER_HEADER
#define CROSSOVER_HEADER

#include "Geno/individual.h"

namespace Geno{
	class Crossover{
	public:
		Crossover(){}
		Crossover(const Crossover &c){
			this->requiredParents_ = c.requiredParents_;
		}
		virtual ~Crossover(){}
		virtual void operator()(Individual *ind1, Individual *ind2) = 0;
		virtual Crossover* clone(void) = 0;
		size_t requiredParents(void){
			return requiredParents_;
		}
	protected:
		int requiredParents_ = 2;
	};
}

#endif