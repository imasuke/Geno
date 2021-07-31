// AlternationModel.h
#ifndef ALTERNATION_MODEL_HEADER
#define ALTERNATION_MODEL_HEADER

#include <vector>

#include "Individual.h"
#include "Crossover.h"

namespace Geno{

	// Abstract class
	class AlternationModel{
	public:
		typedef struct{
			Crossover *crossover;
			MutateOperator mutate;
			FitnessFunction ff;
		} OperatorSet;

		AlternationModel(){}
		virtual ~AlternationModel(){}
		virtual void alternatePopulation(Population *population, const OperatorSet &ops, const bool is_maximize) = 0;
	
	protected:
		void mutateChildren(double mutation_rate);
		void evaluateChildren();
	
	protected:
		Population children_;
		OperatorSet ops_;
	};

	// Roulette Selection
	class RouletteSelection : public AlternationModel{
	public:
		RouletteSelection();	
		RouletteSelection(double crossover_rate, double mutation_rate);
		~RouletteSelection();
		void alternatePopulation(Population *population, const OperatorSet &ops, const bool is_maximize);
	private:
		void crossoverChildren(double crossover_rate);
	private:
		double crossover_rate_;
		double mutation_rate_;
	};

	// Tournament Selection
	class TournamentSelection : public AlternationModel{
	public:
		TournamentSelection(unsigned int tournament_size, double crossover_rate, double mutation_rate);
		~TournamentSelection();
		void alternatePopulation(Population *population, const OperatorSet &ops, const bool is_maximize);
	private:
		void crossoverChildren(double crossover_rate);
	private:
		unsigned int tournament_size_;
		double crossover_rate_;
		double mutation_rate_;
	};

	// Miniam Generation Gap(MGG)
	class MGG : public AlternationModel{
	public:
		MGG(size_t children_size, double mutation_rate);
		~MGG();
		void alternatePopulation(Population *population, const OperatorSet &ops, bool is_maximize);
	private:
		void makeChildren(Individual *parent1, Individual *parent2);
		Individual* findElite(bool is_maximize);
	private:
		size_t children_size_;
		double mutation_rate_;
	};

}

#endif