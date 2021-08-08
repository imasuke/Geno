// ArrayCrossover.h
#ifndef ARRAY_CROSSOVER
#define ARRAY_CROSSOVER

#include <utility>
#include <vector>
#include <algorithm>
#include "Geno/Individual.h"
#include "Geno/util.h"
#include "Crossover.h"

namespace Geno::crossover{
	template <class T>
	void onePointCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size) {
		Randomizer rand;
		unsigned int cross_point = rand.randomInt(1, gene_size-2);

		// One point crossover
		for(size_t i=0; i<gene_size; i++){
			if(i > cross_point){
				std::swap(gene1->at(i), gene2->at(i));
			}
		}
	}

	template <class T>
	void twoPointCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size){
		Randomizer rand;
		unsigned int cross_point1, cross_point2;

		// Choice two different crossover points
		do{
			cross_point1 = rand.randomInt(1, gene_size-2);
			cross_point2 = rand.randomInt(1, gene_size-2);
		} while(cross_point1 == cross_point2);

		// Make sure cross_point1 < cross_point2
		if(cross_point1 > cross_point2) std::swap(cross_point1, cross_point2);

		// Two point crossover
		for(size_t i=0; i<gene_size; i++){
			if(cross_point1 < i && i < cross_point2){
				std::swap(gene1->at(i), gene2->at(i));
			}
		}	
	}

	template <class T>
	void uniformCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size){
		Randomizer rand;

		// Uniform crossover
		for(size_t i=0; i<gene_size; i++){
			if(rand.randomDouble(1.0) > 0.5){
				std::swap(gene1->at(i), gene2->at(i));
			}
		}
	}

	template <class T>
	std::vector<T> cyclicCrossoverChild(const std::vector<T> *gene1, const std::vector<T> *gene2, size_t gene_size, unsigned int start){
		std::vector<T> child(gene_size);
		std::vector<bool> flag(gene_size, false);
		unsigned int s = start;

		while(!flag[s]){
			child.at(s) = gene1->at(s);
			flag[s] = true;
			auto next = std::find(gene1->begin(), gene1->end(), gene2->at(s));
			s = std::distance(gene1->begin(), next);
		}
		for(size_t i=0; i<gene_size; i++){
			if(!flag[i]){
				child.at(i) = gene2->at(i);
				flag[i] = true;
			}
		}

		return child;
	}

	template <class T>
	void cyclicCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size){
		std::vector<T> child1, child2;
		Randomizer rand;
		unsigned int start;

		start = rand.randomInt(gene_size-1);
		child1 = cyclicCrossoverChild(gene1, gene2, gene_size, start);
		child2 = cyclicCrossoverChild(gene2, gene1, gene_size, start);
		std::copy(child1.begin(), child1.end(), gene1->begin());
		std::copy(child2.begin(), child2.end(), gene2->begin());
	}

	template <class T>
	void partiallyMappedCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size){
		std::vector<T> child1(gene_size), child2(gene_size);
		Randomizer rand;
		unsigned int i;

		// copy parents to children
		std::copy(gene1->begin(), gene1->end(), child1.begin());
		std::copy(gene2->begin(), gene2->end(), child2.begin());

		// crossover
		i = rand.randomInt(gene_size-1); // starts from random position
		while(i < gene_size){
			unsigned int j1, j2;
			auto it1 = std::find(child1.begin(), child1.end(), child2.at(i));
			auto it2 = std::find(child2.begin(), child2.end(), child1.at(i));
			j1 = std::distance(child1.begin(), it1);
			j2 = std::distance(child2.begin(), it2);
			std::swap(child1.at(i), child2.at(i));
			std::swap(child1.at(j1), child2.at(j2));
			i++;
		}
		// restore children to input pointers
		std::copy(child1.begin(), child1.end(), gene1->begin());
		std::copy(child2.begin(), child2.end(), gene2->begin());
	}

	template <class T>
	std::vector<T> orderCrossoverChild(const std::vector<T> *gene1, const std::vector<T> *gene2, size_t gene_size, unsigned int start){
		std::vector<T> child(gene_size);
		std::vector<bool> flag(gene_size, false);

		for(unsigned int i=0; i<gene_size; i++){
			if(i < start){
				child.at(i) = gene1->at(i);
				flag[gene1->at(i)] = true;
			}
			else{
				unsigned int j = 0;
				while(flag[gene2->at(j)] && j < gene_size){
					j++;
				}
				child.at(i) = gene2->at(j);
				flag[gene2->at(j)] = true;
			}
		}
		return child;
	}

	template <class T>
	void orderCrossover(std::vector<T> *gene1, std::vector<T> *gene2, size_t gene_size){
		std::vector<T> child1, child2;
		Randomizer rand;
		unsigned int start;

		start = rand.randomInt(gene_size-1);
		child1 = orderCrossoverChild(gene1, gene2, gene_size, start);
		child2 = orderCrossoverChild(gene2, gene1, gene_size, start);
		std::copy(child1.begin(), child1.end(), gene1->begin());
		std::copy(child2.begin(), child2.end(), gene2->begin());
	}

	// Crossover template class
	template <class T>
	class OnePointCrossover : public Crossover{
	public:
		OnePointCrossover(){
			requiredParents_ = 2;
		}
		OnePointCrossover(const OnePointCrossover &c) : Crossover(c){
		}
		~OnePointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				onePointCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		OnePointCrossover* clone(void){
			return new OnePointCrossover(*this);
		}
	};

	template <class T>
	class TwoPointCrossover : public Crossover{
	public:
		TwoPointCrossover(){
			requiredParents_ = 2;
		}
		TwoPointCrossover(const TwoPointCrossover &c) : Crossover(c){
		}
		~TwoPointCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				twoPointCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		TwoPointCrossover* clone(void){
			return new TwoPointCrossover(*this);
		}
	};

	template <class T>
	class UniformCrossover : public Crossover{
	public:
		UniformCrossover(){
			requiredParents_ = 2;
		}
		UniformCrossover(const UniformCrossover &c) : Crossover(c){
		}
		~UniformCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				uniformCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		UniformCrossover* clone(void){
			return new UniformCrossover(*this);
		}
	};

	template <class T>
	class CyclicCrossover : public Crossover{
	public:
		CyclicCrossover(){
			requiredParents_ = 2;
		}
		CyclicCrossover(const CyclicCrossover &c) : Crossover(c){
		}
		~CyclicCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				cyclicCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		CyclicCrossover* clone(void){
			return new CyclicCrossover(*this);
		}
	};

	template <class T>
	class PartiallyMappedCrossover : public Crossover{
	public:
		PartiallyMappedCrossover(){
			requiredParents_ = 2;
		}
		PartiallyMappedCrossover(const PartiallyMappedCrossover &c) : Crossover(c){
		}
		~PartiallyMappedCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				partiallyMappedCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		PartiallyMappedCrossover* clone(void){
			return new PartiallyMappedCrossover(*this);
		}
	};

	template <class T>
	class OrderCrossover : public Crossover{
	public:
		OrderCrossover(){
			requiredParents_ = 2;
		}
		OrderCrossover(const OrderCrossover &c) : Crossover(c){
		}
		~OrderCrossover(){
		}
		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind2->form == Individual::ARRAY){
				T *array_ind1 = static_cast<T*>(ind1);
				T *array_ind2 = static_cast<T*>(ind2);
				orderCrossover(&(array_ind1->genotype), &(array_ind2->genotype), array_ind1->gene_size);
			}
		}
		OrderCrossover* clone(void){
			return new OrderCrossover(*this);
		}
	};

	template <class T>
	class BlxAlphaCrossover : public Crossover{
	public:
		BlxAlphaCrossover(double alpha) : alpha_(alpha){
			requiredParents_ = 2;
		}
		BlxAlphaCrossover(const BlxAlphaCrossover &c) : Crossover(c){
			this->alpha_ = c.alpha_;
		}
		~BlxAlphaCrossover(){
		}
		BlxAlphaCrossover* clone(void){
			return new BlxAlphaCrossover(*this);
		}

		void operator()(Individual *ind1, Individual *ind2){
			if(ind1->form == Individual::ARRAY && ind1->gtype == Individual::REAL 
			 && ind2->form == Individual::ARRAY && ind2->gtype == Individual::REAL){
				T *rind1 = static_cast<T*>(ind1);
				T *rind2 = static_cast<T*>(ind2);
				blxAlphaCrossover(rind1, rind2);
			}
		}

		void blxAlphaCrossover(T *rind1, T *rind2){
			Randomizer rand;
			double vmax, vmin, vdiff;
			unsigned int n;

			n = rind1->genotype.size();

			for(size_t i=0; i<n; i++){
				vmin = std::min(rind1->genotype[i], rind2->genotype[i]);
				vmax = std::max(rind1->genotype[i], rind2->genotype[i]);
				vdiff = std::abs(rind1->genotype[i] - rind2->genotype[i]);
				rind1->genotype[i] = rand.randomDouble(vmin - alpha_ * vdiff, vmax + alpha_ * vdiff);
				rind2->genotype[i] = rand.randomDouble(vmin - alpha_ * vdiff, vmax + alpha_ * vdiff);
			}
		}

	private:
		double alpha_;
	};
}

#endif