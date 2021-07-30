// TSP.cpp
#include <iostream>
#include <vector>
#include <cmath>

#include "Geno.h"
#include "matplotlib-cpp/matplotlibcpp.h"

using std::vector;
using namespace Geno;
namespace plt = matplotlibcpp;

const vector<vector<int>> CITY_POSITIONS = {
	{20, 34}, {60, 95}, {11, 38}, {3, 74}, {29, 54}, {77, 5}, {42, 86}, {82, 67}, {54, 33}, {12, 5},
	{55, 74}, {19, 61}, {14, 5}, {97, 65}, {33, 67}, {26, 43}, {2, 84}, {38, 23}, {84, 64}, {53, 58}
};

class TSPFitness{
public:
	TSPFitness(){
		city_distance_.resize(CITY_POSITIONS.size());

		// calculate distances between cities
		for(unsigned int i=0; i<CITY_POSITIONS.size(); i++){
			city_distance_[i].resize(CITY_POSITIONS.size());
			for(unsigned j=0; j<CITY_POSITIONS.size(); j++){
				if(i != j){
					double x_dif = CITY_POSITIONS[i][0] - CITY_POSITIONS[j][0];
					double y_dif = CITY_POSITIONS[i][1] - CITY_POSITIONS[j][1];
					city_distance_[i][j] = std::sqrt(x_dif * x_dif + y_dif * y_dif);
				}
				else{
					city_distance_[i][j] = 0.0;
				}
				
			}
		}
	}

	~TSPFitness(){
	}

	double operator()(const Individual &ind){
		IntegerArrayIndividual &iind = (IntegerArrayIndividual&)ind;
		double distance = 0;
		int start = iind.genotype[0], city;

		city = start;
		for(size_t i=1; i<iind.genotype.size(); i++){
			int next = iind.genotype[i];
			distance += city_distance_[city][next];
			city = next;
		}
		distance += city_distance_[city][start];
		return distance;
	}

private:
	vector<vector<double>> city_distance_;
};

class MyObserver : public Observer{
	void generationAltered(GA *ga){
		int gen = ga->getCurrentGeneration();
		std::cout << "gen:" << gen << " elite:" << ga->getEliteIndividual()->fitness << std::endl;

		if(gen % 100 == 0){
			IntegerArrayIndividual *elite = (IntegerArrayIndividual*)ga->getEliteIndividual();
			vector<double> x(CITY_POSITIONS.size()), y(CITY_POSITIONS.size());

			for(unsigned int i=0; i<elite->genotype.size(); i++){
				x[i] = CITY_POSITIONS[elite->genotype[i]][0];
				y[i] = CITY_POSITIONS[elite->genotype[i]][1];
			}
			plt::clf();
			plt::xlim(0, 100);
			plt::ylim(0, 100);
			plt::scatter(x, y, 10);
			plt::plot(x, y);
			plt::grid(true);
			plt::title("City Map");
			plt::pause(0.01);
		}
	}
	
	void evolutionEnded(GA *ga){
		IntegerArrayIndividual *best = (IntegerArrayIndividual*) ga->getEliteIndividual();
		std::cout << "best fitness: " << best->fitness << std::endl;
		std::cout << "best: " ;
		for(unsigned int i=0; i<best->genotype.size(); i++){
			std::cout << best->genotype[i] << " " ;
		}
		std::cout << std::endl;
	}
};

int main(void){
	IntegerArrayIndividual::Factory factory;
	factory.geneSize(CITY_POSITIONS.size())
		.initializer(IntegerArrayIndividual::uniqueInitializer(0, CITY_POSITIONS.size()-1))
		.crossover(IntegerArrayIndividual::orderCrossover())
		.mutate(IntegerArrayIndividual::swapMutate());
	TSPFitness ff;
	GA ga(factory, ff);
	MyObserver observer;
	GA::Parameter param;
	MGG mgg(20);

	param.population_size = 100;
	param.max_generation = 10000;
	param.goal_fitness = 0; // Distance should be small value
	param.is_maximize = false; // Fitness should be minimized
	ga.setParameter(param);
	ga.setAlternationModel(mgg);
	ga.addObserver(observer);
	ga.enableStatistics(true);

	ga.evolve();
	getchar();

	return 0;
}

