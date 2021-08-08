// RealVectorIndividual.h
#ifndef REAL_VECTOR_INDIVIDUAL_HEADER
#define REAL_VECTOR_INDIVIDUAL_HEADER

#include "Geno/IndividualFactory.h"
#include "Geno/ArrayCrossover.h"

namespace Geno{
	
	class RealVectorIndividual : public ArrayIndividual<double>{
	public:
		typedef std::function <void(std::vector<double>*)> Initializer;
		using OnePointCrossover = crossover::OnePointCrossover<RealVectorIndividual>;
		using TwoPointCrossover = crossover::TwoPointCrossover<RealVectorIndividual>;
		using UniformCrossover = crossover::UniformCrossover<RealVectorIndividual>;
		using BlxAlphaCrossover = crossover::BlxAlphaCrossover<RealVectorIndividual>;

		RealVectorIndividual(const size_t gene_size, const Initializer&);
		RealVectorIndividual(const RealVectorIndividual&);
		~RealVectorIndividual();
		Individual* clone();
		static Initializer randomInitializer(const double value_min, const double value_max);
		static MutateOperator randomMutate(const double value_min, const double value_max);

		class Factory : public IndividualFactory{
		public:
			Factory();
			~Factory();
			Individual* create();
			Factory& geneSize(const size_t gene_size);
			Factory& initializer(const Initializer &init);

		private:
			size_t gene_size_;
			Initializer init_;
		};

	public:
		Initializer init;
	};
}

#endif