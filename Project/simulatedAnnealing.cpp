#include "data.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <random>

//using namespace std;
//vector<pair<int,int>> simulatedAnnealing(vector<int> solution, int binSize, int quantity, int iterations, bool uniformRealDistributionIsSet, string showBestOrAll) {
//
//    int result = knapsack(solution, binSize, quantity);
//    int nextResult, bestResult;
//    double boltzmannDistribution;
//    vector<int> bestSolution = solution;
//    vector<int> nextSolution = solution;
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<> uniformRealDistribution(0.0, 1.0);
//    normal_distribution<double> normalDistribution(0.5,0.25);
//    int iteration_counter;
//
//    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
//        shuffle(begin(nextSolution), end(nextSolution), gen);
//        nextResult = knapsack(nextSolution, binSize, quantity);
//        boltzmannDistribution = exp(-abs(result - nextResult) / (iterations/(iteration_counter+1)));
//        if ( nextResult < result ){
//            solution = nextSolution;
//            result = nextResult;
//            //rozkład liniowy
//        } else if (uniformRealDistributionIsSet && (uniformRealDistribution(gen) < boltzmannDistribution)) {
//            solution = nextSolution;
//            result = nextResult;
//            //rozkład normalny
//        } else if (!uniformRealDistributionIsSet && (normalDistribution(gen) < boltzmannDistribution)) {
//            solution = nextSolution;
//            result = nextResult;
//        }
//        bestResult = knapsack(bestSolution, binSize, quantity);
//        if (result < bestResult){
//            bestSolution = solution;
//            bestResult = result;
//        }
//        if(showBestOrAll == "all"){
//            cout  << "Amounts of bins in first run: " << result << endl << "Amounts of bins in best run: "
//                  << bestResult << endl << "Iterations: " << iteration_counter << endl;
//        }
//    }
//
//    if(showBestOrAll == "best"){
//        cout << "Amount of bins in best run: " << bestResult << endl << "Iterations: " << iteration_counter << endl;
//        for(auto i: bestSolution){
//            cout << i << ", ";
//        }}
//}