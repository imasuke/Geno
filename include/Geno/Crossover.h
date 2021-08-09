// Crossover.h
#ifndef CROSSOVER_HEADER
#define CROSSOVER_HEADER

#include <vector>
#include "Geno/individual.h"

namespace Geno{
	// Abstract base class for crossover
	class Crossover{
	public:
		Crossover() : requiredParents_(0) {}
		Crossover(const int requiredParents) : requiredParents_(requiredParents){}
		Crossover(const Crossover &c){
			this->requiredParents_ = c.requiredParents_;
		}
		virtual ~Crossover(){}
		//virtual void operator()(Individual *ind1, Individual *ind2) = 0;
		virtual Crossover* clone(void) = 0;
		size_t requiredParents(void){
			return requiredParents_;
		}
	protected:
		int requiredParents_;
	};

	// Abstract class for 2 parents crossover
	class Crossover2p : public Crossover{
	public:
		Crossover2p() : Crossover(2) {}
		Crossover2p(const Crossover2p &c) : Crossover(c) {
		}
		virtual ~Crossover2p(){}
		virtual void operator()(Individual *ind1, Individual *ind2) = 0;
	};

	// Abstract class for N parents crossover
	class CrossoverNp : public Crossover{
	public:
		CrossoverNp(){}
		CrossoverNp(const CrossoverNp &c) : Crossover(c) {
		}
		virtual ~CrossoverNp(){}
		virtual void operator()(std::vector<Individual*> *individuals) = 0;
	};
}

#endif