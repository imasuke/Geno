// Crossover.h
#ifndef CROSSOVER_HEADER
#define CROSSOVER_HEADER

#include "Geeni/individual.h"

namespace Geeni{

	class Crossover{
	public:
		Crossover(){}
		virtual ~Crossover(){}
		virtual void operator()(Individual *ind1, Individual *ind2) = 0;
		virtual size_t requiredParents(void) = 0;
	};
	
	class OnePointCrossover : public Crossover{
	public:
		OnePointCrossover();
		~OnePointCrossover();
		void operator()(Individual *ind1, Individual *ind2);
		size_t requiredParents(void);
	private:
		const int kRequiredParents = 2;
	};
}

#endif