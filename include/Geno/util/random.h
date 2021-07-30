// random.h
#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <random>

namespace Geno{
	class Randomizer{
	public:
		Randomizer();
		~Randomizer();
		void init();
		int randomInt(int min, int max);
		int randomInt(int max);
		double randomDouble(double min, double max);
		double randomDouble(double max);
	private:
		std::mt19937 *mt;
	};
}

#endif