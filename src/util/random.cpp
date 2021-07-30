// random.cpp
#include "Geno/util/random.h"

namespace Geno{
	Randomizer::Randomizer(){
		init();
	}

	Randomizer::~Randomizer(){
		delete mt;
	}

	void Randomizer::init(){
		std::random_device rd;
		mt = new std::mt19937(rd());
	}

	int Randomizer::randomInt(int min, int max){
		std::uniform_int_distribution<int> gen(min, max);
		return gen(*mt);
	}

	int Randomizer::randomInt(int max){
		return randomInt(0, max);
	}

	double Randomizer::randomDouble(double min, double max){
		std::uniform_real_distribution<double> gen(min, max);
		return gen(*mt);
	}

	double Randomizer::randomDouble(double max){
		return randomDouble(0.0, max);
	}
}

