// Crossover.h
#ifndef CROSSOVER_HEADER
#define CROSSOVER_HEADER

#include "Geeni/individual.h"
#include "ArrayCrossover.h"

namespace Geeni{

	class Crossover{
	public:
		Crossover(){}
		virtual ~Crossover(){}
		virtual void operator()(Individual *ind1, Individual *ind2) = 0;
		virtual size_t requiredParents(void) = 0;
	};

	template <class T>
	class OnePointCrossover : public Crossover{
	public:
		OnePointCrossover(){
		}
		~OnePointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				Geeni::onePointCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		size_t requiredParents(void){
			return kRequiredParents;
		}
	private:
		const int kRequiredParents = 2;
	};

	template <class T>
	class TwoPointCrossover : public Crossover{
	public:
		TwoPointCrossover(){
		}
		~TwoPointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				Geeni::twoPointCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		size_t requiredParents(void){
			return kRequiredParents;
		}
	private:
		const int kRequiredParents = 2;
	};

	template <class T>
	class UniformCrossover : public Crossover{
	public:
		UniformCrossover(){
		}
		~UniformCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				Geeni::uniformCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		size_t requiredParents(void){
			return kRequiredParents;
		}
	private:
		const int kRequiredParents = 2;
	};
}

#endif