cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0")

find_package(PythonLibs 2.7)

# Sample1: Search all one bit string
add_executable(AllOneBitString AllOneBitString.cpp)
target_link_libraries(AllOneBitString GA ${PYTHON_LIBRARIES})
target_include_directories(AllOneBitString PRIVATE ../include ${PYTHON_INCLUDE_DIRS})

# Sample2: Traveling Salesman Problem(TSP)
add_executable(TSP TSP.cpp)
target_link_libraries(TSP GA ${PYTHON_LIBRARIES})
target_include_directories(TSP PRIVATE ../include ${PYTHON_INCLUDE_DIRS})

# Sample3: Serch optialmal value in Benchmark function
add_executable(BenchmarkFunction BenchmarkFunction.cpp)
target_link_libraries(BenchmarkFunction GA ${PYTHON_LIBRARIES})
target_include_directories(BenchmarkFunction PRIVATE ../include ${PYTHON_INCLUDE_DIRS})

