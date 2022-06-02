#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;
void hillClimbing(vector<int> data, int binSize, int quantity, int iterations) {

    int amountOfBins = howManyBin(data, binSize, quantity);
    int lowestAmountOfBins = amountOfBins;
    int iteration_counter = 0;

    srand((unsigned) time(NULL));

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        int x = rand() % (end(data) - begin(data));
        for (int j = 0; j < data.size(); ++j) {
            swap(data[x], data[j]);
            amountOfBins = howManyBin(data, binSize, quantity);
            if (amountOfBins < lowestAmountOfBins) {
                lowestAmountOfBins = amountOfBins;
            }
        }

    }
    cout << "Amounts of bins in best run: " << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
     for(auto i: data){
        cout << i << ", ";
     }
}

void hillClimbingRandom(vector<int> solution, int binSize, int quantity, int iterations) {
    int amountOfBins, lowestAmountOfBins = howManyBin(solution, binSize, quantity);
    int iteration_counter = 0;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        shuffle(begin(solution), end(solution), mt19937(random_device()()));
        amountOfBins = howManyBin(solution, binSize, quantity);
        if (amountOfBins < lowestAmountOfBins) {
            lowestAmountOfBins = amountOfBins;
        }
    }
    cout << "Amounts of bins in best run: " << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
    for(auto i: solution){
        cout << i << ", ";
    }
}