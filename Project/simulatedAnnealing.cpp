#include "data.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;
void simulatedAnnealing(vector<int> solution, int binSize, int quantity, int iterations) {

    vector<int> bestSolution = solution;
    vector<int> nextSolution = solution;
    int iteration_counter = 1;

    for (int i = 0; i < iterations; ++i) {
        shuffle(begin(nextSolution), end(nextSolution), mt19937(random_device()()));
        if (howManyBin(nextSolution, binSize, quantity) < howManyBin(solution, binSize, quantity)) {
            solution = nextSolution;
        } else {
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.0, 1.0);
            if (dis(gen) < exp(-abs(howManyBin(solution, binSize, quantity) - howManyBin(nextSolution, binSize, quantity)) *
                               iteration_counter / 1000)) {
                solution = nextSolution;
            }
        }
        if (howManyBin(solution, binSize, quantity) < howManyBin(bestSolution, binSize, quantity)) bestSolution = solution;
        cout  << "Amounts of bins in this run: " << howManyBin(solution, binSize, quantity) << endl << "Amounts of bins in best run: "
              << howManyBin(bestSolution, binSize, quantity) << endl << "Iterations: " << iteration_counter << endl;
        iteration_counter++;
    }
}