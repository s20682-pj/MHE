#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;
void hillClimbing(vector<int> solution, int binSize, int quantity, int iterations) {

    int amountOfBins = howManyBin(solution, binSize, quantity);
    int lowestAmountOfBins = amountOfBins;

    srand((unsigned) time(NULL));

    for (int i = 0; i < iterations; ++i) {
        int x = rand() % (end(solution) - begin(solution));
        for (int j = 0; j < solution.size(); ++j) {
            swap(solution[x], solution[j]);
            amountOfBins = howManyBin(solution, binSize, quantity);
            if (amountOfBins < lowestAmountOfBins) {
                lowestAmountOfBins = amountOfBins;
            }
        }
        cout  << "Amounts of bins in this run: " << amountOfBins << endl << "Amounts of bins in best run: "
        << lowestAmountOfBins << endl << "Iterations: " << i << endl;
    }
}

void hillClimbingRandom(vector<int> solution, int binSize, int quantity, int iterations) {
    int amountOfBins, lowestAmountOfBins = howManyBin(solution, binSize, quantity);

    for (int i = 0; i < iterations; ++i) {
        shuffle(begin(solution), end(solution), mt19937(random_device()()));
        amountOfBins = howManyBin(solution, binSize, quantity);
        if (amountOfBins < lowestAmountOfBins) {
            lowestAmountOfBins = amountOfBins;
        }
        cout  << "Amounts of bins in this run: " << amountOfBins << endl << "Amounts of bins in best run: "
        << lowestAmountOfBins << endl << "Iterations: " << i << endl;
    }
}