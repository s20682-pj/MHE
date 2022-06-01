#include <iostream>
#include <array>
#include <vector>

#ifndef BINPACKINGPROBLEM_DATA_H
#define BINPACKINGPROBLEM_DATA_H

using namespace std;

vector<int> dataGenerator(std::vector<int> data, int minRange, int maxRange, int quantity);
int howManyBin(std::vector<int> data, int binSize, int quantity);
void hillClimbingRandom(std::vector<int> data, int binSize, int quantity, int iterations);
void hillClimbing(std::vector<int> data, int binSize, int quantity, int iterations);
void tabuSearch(std::vector<int> data, int binSize, int quantity, int tabuSize, int iterations);
void simulatedAnnealing(std::vector<int> data, int binSize, int quantity, int iterations);

#endif //BINPACKINGPROBLEM_DATA_H