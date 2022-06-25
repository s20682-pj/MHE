#include <iostream>
#include <array>
#include <vector>

#ifndef KNAPSACKPROBLEM_DATA_H
#define KNAPSACKPROBLEM_DATA_H

using namespace std;

int knapsack(vector<pair<int, int>> data, int backpackSize);
vector<pair<int,int>> hillClimbing(vector<pair<int, int>> data, int backpackSize, int iterations);
vector<pair<int,int>> hillClimbingRandom(vector<pair<int, int>> data, int backpackSize, int iterations);
vector<pair<int,int>> tabuSearch(vector<pair<int, int>> data, int binSize, int tabuSize, int iterations);
vector<pair<int,int>> simulatedAnnealing(vector<pair<int, int>> data, int backpackSize, int iterations, bool uniformRealDistributionIsSet);
vector<pair<int,int>> genetic(vector<pair<int, int>> data, int backpackSize, int populationSize, string crossing, string mutation, string ending, int generations);
#endif //KNAPSACKPROBLEM_DATA_H