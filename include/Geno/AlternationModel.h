// AlternationModel.h
#ifndef ALTERNATION_MODEL_HEADER
#define ALTERNATION_MODEL_HEADER

#include <vector>

#include "Individual.h"

namespace Geno{

	// Abstract class
	class AlternationModel{
	public:
		AlternationModel(){}
		virtual ~AlternationModel(){}
		virtual void makeChildren(Population *population, bool is_maximize) = 0;
		virtual void alternatePopulation(Population *population, bool is_maximize) = 0;
		virtual void mutateChildren(double mutation_rate);
		virtual void evaluateChildren(const FitnessFunction &ff);

	protected:
		Population children_;
	};

	// Roulette Selection
	class RouletteSelection : public AlternationModel{
	public:
		RouletteSelection();
		~RouletteSelection();
		void makeChildren(Population *population, bool is_maximize);
		void alternatePopulation(Population *population, bool is_maximize);
	private:
		void crossoverChildren(double crossover_rate);
	};

	// Tournament Selection
	class TournamentSelection : public AlternationModel{
	public:
		TournamentSelection(unsigned int tournament_size);
		~TournamentSelection();
		void makeChildren(Population *population, bool is_maximize);
		void alternatePopulation(Population *population, bool is_maximize);
	private:
		void crossoverChildren(double crossover_rate);
	private:
		unsigned int tournament_size_;
	};

	// Miniam Generation Gap(MGG)
	class MGG : public AlternationModel{
	public:
		MGG(size_t children_size);
		~MGG();
		void makeChildren(Population *population, bool is_maximize);
		void alternatePopulation(Population *population, bool is_maximize);
	private:
		Individual* findElite(bool is_maximize);
	private:
		size_t children_size_;
	};

}

#endif