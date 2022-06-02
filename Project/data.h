#include <iostream>
#include <array>
#include <vector>

#ifndef BINPACKINGPROBLEM_DATA_H
#define BINPACKINGPROBLEM_DATA_H

using namespace std;

int howManyBin(vector<int> data, int binSize, int quantity);
void hillClimbingRandom(vector<int> data, int binSize, int quantity, int iterations);
void hillClimbing(vector<int> data, int binSize, int quantity, int iterations);
void tabuSearch(vector<int> data, int binSize, int quantity, int tabuSize, int iterations);
void simulatedAnnealing(vector<int> solution, int binSize, int quantity, int iterations, bool uniformRealDistributionIsSet);

#endif //BINPACKINGPROBLEM_DATA_H