// GA.h
#ifndef GA_HEADER
#define GA_HEADER

#include "AlternationModel.h"
#include "Individual.h"
#include "Statistics.h"

#include <vector>

namespace Geno{
	class GA;

	class Observer{
	public:
		Observer(){}
		virtual ~Observer(){}
		virtual void evolutionStarted(GA *ga){}
		virtual void evolutionEnded(GA *ga){}
		virtual void generationAltered(GA *ga){}
	};

	class GA{
	public:
		// Parameter for Genetic Algorithm
		struct Parameter{
			unsigned int population_size;
			unsigned int max_generation;
			double goal_fitness;
			bool is_maximize;
			bool elite_strategy;

			Parameter() : 
			 population_size(10), max_generation(100), goal_fitness(1.0), is_maximize(true), elite_strategy(true)
			{
			}
		};

		GA(IndividualFactory&, FitnessFunction);
		~GA();
		void evolve();
		void addObserver(Observer&);
		void removeObserver();
		void setParameter(GA::Parameter&);
		Parameter getParameter() const;
		Population getPopulation() const;
		Statistics* getStatistics() const;
		void setAlternationModel(AlternationModel&);
		void setFitnessFuction(FitnessFunction);
		int getCurrentGeneration() const;
		Individual* getEliteIndividual() const;
		void enableStatistics(bool flag);

	private:
		void initPopulation();
		void evaluatePopulation(Population *population);
		void eliteStrategy();
		Individual* findElite(bool is_maximize);

	private:
		Population population;
		Population children;
		IndividualFactory *factory;
		AlternationModel *alt_model;
		FitnessFunction ff;
		Parameter *param;
		Observer *observer;
		unsigned int gen;
		Individual *elite;
		Statistics *stat;
		bool statistics_enabled;
	};

}

#endif