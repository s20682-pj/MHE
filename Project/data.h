#include <iostream>
#include <array>
#include <vector>

#ifndef BINPACKINGPROBLEM_DATA_H
#define BINPACKINGPROBLEM_DATA_H

using namespace std;

int howManyBin(vector<int> data, int binSize, int quantity);
vector<int> hillClimbingRandom(vector<int> data, int binSize, int quantity, int iterations, string showBestOrAll);
vector<int> hillClimbing(vector<int> data, int binSize, int quantity, int iterations, string showBestOrAll);
vector<int> tabuSearch(vector<int> data, int binSize, int quantity, int tabuSize, int iterations, string showBestOrAll);
vector<int> simulatedAnnealing(vector<int> solution, int binSize, int quantity, int iterations, bool uniformRealDistributionIsSet, string showBestOrAll);

#endif //BINPACKINGPROBLEM_DATA_H