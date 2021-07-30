// Statistics.h
#ifndef STATISTICS_HEADER
#define STATISTICS_HEADER

#include "Individual.h"

#include <vector>

namespace Geno{
	class Statistics{
	public:
		Statistics();
		~Statistics();
		std::vector<double> maxFitnessReport();
		std::vector<double> minFitnessReport();
		std::vector<double> meanFitnessReport();
		void collectPopulationData(const std::vector<Individual*> &population);

	private:
		std::vector<double> maxFitness;
		std::vector<double> minFitness;
		std::vector<double> meanFitnesss;
	};
}

#endif
