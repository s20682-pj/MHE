#include "data.h"
#include <list>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;
vector<int> tabuSearch(vector<int> solution, int binSize, int quantity, int tabu_size, int iterations){

    int amountOfBins = howManyBin(solution, binSize, quantity);
    int lowestAmountOfBins = amountOfBins;
    vector<int> bestSolution = solution;
    vector<vector<int>> tabuList = {solution};
    bool betterSolutionIsFound;
    int tabuListOffset = 1;
    int iteration_counter;
    srand((unsigned) time(NULL));

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        betterSolutionIsFound = false;
        int x = rand() % (end(solution) - begin(solution));
        for (int j = 0; j < solution.size(); ++j) {
            swap(solution[x], solution[j]);
            amountOfBins = howManyBin(solution, binSize, quantity);
            bool isNotInTabu = find(tabuList.begin(), tabuList.end(), solution) == tabuList.end();
            if (amountOfBins <= lowestAmountOfBins and  isNotInTabu){
                lowestAmountOfBins = amountOfBins;
                bestSolution = solution;
                betterSolutionIsFound = true;
            }
        }

        if (betterSolutionIsFound){
            tabuList.push_back(bestSolution);
            if (tabuList.size() > tabu_size) {
                tabuList.erase(tabuList.begin());
            }
            tabuListOffset = 1;
        } else if ((int)tabuList.size()-tabuListOffset >= 0) {
            solution = tabuList[tabuList.size() - tabuListOffset];
            tabuListOffset++;
        }
        else{
            break;
        }
    }
    cout << "Amount of bins in best run: " << lowestAmountOfBins << endl << "Iterations: " << iteration_counter << endl;
    for(auto i: bestSolution){
        cout << i << ", ";
    }

}