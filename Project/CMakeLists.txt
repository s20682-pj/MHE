cmake_minimum_required(VERSION 3.19.2)
project(KnapsackProblem)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnapsackProblem
        main.cpp
        hillClimbing.cpp
        tabuSearch.cpp simulatedAnnealing.cpp knapsack.cpp data.h genetic.cpp genetic_mutation.cpp genetic_crossing.cpp genetic_tournament.cpp genetic_fitness.cpp geneticDemo.cpp)
