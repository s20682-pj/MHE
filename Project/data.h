#include <iostream>
#include <array>
#include <vector>

#ifndef KNAPSACKPROBLEM_DATA_H
#define KNAPSACKPROBLEM_DATA_H

using namespace std;

int knapsack(vector<pair<int, int>> data, int backpackSize, int quantity);
vector<int> hillClimbing(vector<pair<int, int>> data, int backpackSize, int quantity, int iterations);
vector<int> hillClimbingRandom(vector<pair<int, int>> data, int binSize, int quantity, int iterations;
vector<int> tabuSearch(vector<pair<int, int>> data, int binSize, int quantity, int tabuSize, int iterations, string showBestOrAll);
vector<int> simulatedAnnealing(vector<pair<int, int>> data, int binSize, int quantity, int iterations, bool uniformRealDistributionIsSet, string showBestOrAll);

#endif //KNAPSACKPROBLEM_DATA_H