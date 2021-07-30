// Selection.h
#ifndef SELECTION_HEADER
#define SELECTION_HEADER

#include "Geno/Individual.h"

namespace Geno{
	Population rouletteSelection(const Population &org, unsigned int n, bool select_higher_fitness);
	Individual* rouletteSelection(const Population &org, bool select_higher_fitness);
	Population tournamentSelection(const Population &org, unsigned int n, unsigned int tournament_size, bool select_higher_fitness);
	Individual* tournamentSelection(const Population &org, unsigned int tournament_size, bool select_higher_fitness);
}

#endif