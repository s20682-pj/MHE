cmake_minimum_required(VERSION 3.20)
project(BinPackingProblem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinPackingProblem
        main.cpp
        hillClimbing.cpp
        tabuSearch.cpp simulatedAnnealing.cpp knapsack.cpp data.h genetic.cpp)
