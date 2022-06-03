#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;
vector<int> hillClimbing(vector<int> solution, int binSize, int quantity, int iterations, string showBestOrAll) {

    int amountOfBins = howManyBin(solution, binSize, quantity);
    int lowestAmountOfBins = amountOfBins;
    int iteration_counter;

    srand((unsigned) time(NULL));

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        int x = rand() % (end(solution) - begin(solution));
        for (int j = 0; j < solution.size(); ++j) {
            swap(solution[x], solution[j]);
            amountOfBins = howManyBin(solution, binSize, quantity);
            if (amountOfBins < lowestAmountOfBins) {
                lowestAmountOfBins = amountOfBins;
            }
        }
        if(showBestOrAll == "all"){
            cout  << "Amounts of bins in first run: " << amountOfBins << endl << "Amounts of bins in best run: "
                  << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
        }

    }
    if(showBestOrAll == "best"){
    cout << "Amount of bins in best run: " << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
     for(auto i: solution){
        cout << i << ", ";
     }}

}

vector<int> hillClimbingRandom(vector<int> solution, int binSize, int quantity, int iterations, string showBestOrAll) {
    int amountOfBins, lowestAmountOfBins = howManyBin(solution, binSize, quantity);
    int iteration_counter;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        shuffle(begin(solution), end(solution), mt19937(random_device()()));
        amountOfBins = howManyBin(solution, binSize, quantity);
        if (amountOfBins < lowestAmountOfBins) {
            lowestAmountOfBins = amountOfBins;
        }
        if(showBestOrAll == "all"){
            cout  << "Amounts of bins in first run: " << amountOfBins << endl << "Amounts of bins in best run: "
                  << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
        }
    }
    if(showBestOrAll == "best"){
        cout << "Amount of bins in best run: " << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
        for(auto i: solution){
            cout << i << ", ";
        }}
}