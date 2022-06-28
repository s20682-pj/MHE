#include <iostream>
#include <array>
#include <vector>

#ifndef KNAPSACKPROBLEM_DATA_H
#define KNAPSACKPROBLEM_DATA_H

using namespace std;

int knapsack(vector<pair<int, int>> data, int backpackSize);
vector<pair<int,int>> hillClimbing(vector<pair<int, int>> data, int backpackSize, int iterations, int ifScript, int howLong);
vector<pair<int,int>> hillClimbingRandom(vector<pair<int, int>> data, int backpackSize, int iterations, int ifScript, int howLong);
vector<pair<int,int>> tabuSearch(vector<pair<int, int>> data, int binSize, int tabuSize, int iterations, int ifScript, int howLong);
vector<pair<int,int>> simulatedAnnealing(vector<pair<int, int>> data, int backpackSize, int iterations,
                                         bool uniformRealDistributionIsSet, int ifScript, int howLong);
vector<vector<bool>> genetic(vector<pair<int, int>> data, int backpackSize, int populationSize, const string& crossing,
                             const string& mutation, const string& ending, int generations, int ifScript, int howLong);
vector<vector<bool>> genetic_mutation(vector<vector<bool>> children, string mutation, vector<pair<int, int>> data);
vector<vector<bool>> genetic_crossing(string crossing, vector<int> parent, vector<vector<bool>> population, vector<vector<bool>> children,
                                      vector<pair<int, int>> data);
vector<int> genetic_tournament(vector<int> contestant, vector<int> contestantFitness, vector<int> parent);
vector<int> fitness(int populationSize, vector<pair<int, int>> data, int backpackSize, vector<vector<bool>> population);
vector<vector<int>> geneticDemo(vector<vector<int>> parent);
#endif //KNAPSACKPROBLEM_DATA_H