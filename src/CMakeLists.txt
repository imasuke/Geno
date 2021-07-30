cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0")

add_library(GA SHARED
	GA.cpp
	AlternationModel.cpp
	RouletteSelection.cpp
	TournamentSelection.cpp
	MGG.cpp
	Selection.cpp
	BinaryArrayIndividual.cpp
	IntegerArrayIndividual.cpp
	RealVectorIndividual.cpp
	OnePointCrossover.cpp
	Statistics.cpp
	util/random.cpp
)
target_include_directories(GA PRIVATE ../include)
