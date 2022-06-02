#include "data.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;
void simulatedAnnealing(vector<int> solution, int binSize, int quantity, int iterations, bool uniformRealDistributionIsSet) {

    int result, nextResult, bestResult;
    double boltzmannDistribution;
    vector<int> bestSolution = solution;
    vector<int> nextSolution = solution;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> uniformRealDistribution(0.0, 1.0);
    normal_distribution<double> normalDistribution(0.5,0.25);

    for (int i = 0; i < iterations; ++i) {
        shuffle(begin(nextSolution), end(nextSolution), gen);
        result = howManyBin(solution, binSize, quantity);
        nextResult = howManyBin(nextSolution, binSize, quantity);
        boltzmannDistribution = exp(-abs(result - nextResult) / (iterations/(i+1)));
        if ( nextResult < result ){
            solution = nextSolution;
            result = nextResult;
        } else if (uniformRealDistributionIsSet && (uniformRealDistribution(gen) < boltzmannDistribution)) {
            solution = nextSolution;
            result = nextResult;
        } else if (!uniformRealDistributionIsSet && (normalDistribution(gen) < boltzmannDistribution)) {
            solution = nextSolution;
            result = nextResult;
        }
        bestResult = howManyBin(bestSolution, binSize, quantity);
        if (result < bestResult){
            bestSolution = solution;
            bestResult = result;
        }
        cout  << "Amounts of bins in this run: " << result << endl << "Amounts of bins in best run: "
        << bestResult << endl << "Iterations: " << i << endl;
    }
}