// ArrayMutation.h
#ifndef ARRAY_MUTATION_HEADER
#define ARRAY_MUTATION_HEADER

#include <utility>
#include <vector>
//#include <algorithm>
#include "Geno/Individual.h"
#include "Geno/util.h"
#include "Mutation.h"

namespace Geno::mutation{
	// Mutation template class for array individual
	template <class T>
	class SwapMutation : public Mutation{
	public:
		SwapMutation(){
		}
		SwapMutation(const SwapMutation &c) : Mutation(c){
		}
		~SwapMutation(){
		}
		void operator()(Individual *ind){
			if(ind->genotypeForm() == Individual::ARRAY){
				T *array_ind = static_cast<T*>(ind);
                unsigned int gene_size = array_ind->genotype.size();
                Randomizer rand;
                std::swap(array_ind->genotype.at(rand.randomInt(gene_size-1)), array_ind->genotype.at(rand.randomInt(gene_size-1))); 
			}
		}
		SwapMutation* clone(void){
			return new SwapMutation(*this);
		}
	};

	template <class T>
	class ShuffleMutation : public Mutation{
	public:
		ShuffleMutation(){
		}
		ShuffleMutation(const ShuffleMutation &c) : Mutation(c){
		}
		~ShuffleMutation(){
		}
		void operator()(Individual *ind){
			if(ind->genotypeForm() == Individual::ARRAY){
				T *array_ind = static_cast<T*>(ind);
                unsigned int gene_size = array_ind->genotype.size();
                Randomizer rand;
			    std::random_device rd;
			    unsigned int rindex1, rindex2;

			    rindex1 = rand.randomInt(gene_size-1);
			    rindex2 = rand.randomInt(gene_size-1);
			    if(rindex1 > rindex2) std::swap(rindex1, rindex2);
                std::shuffle(array_ind->genotype.begin()+rindex1 , array_ind->genotype.begin()+rindex2, std::mt19937(rd()));
            }
		}
		ShuffleMutation* clone(void){
			return new ShuffleMutation(*this);
		}
	};
}

#endif