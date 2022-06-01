#include "data.h"
#include <list>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;
void tabuSearch(vector<int> solution, int binSize, int quantity, int tabu_size, int iterations){

    int amountOfBins = howManyBin(solution, binSize, quantity);
    int lowestAmountOfBins = amountOfBins;
    vector<int> bestSolution = solution;
    vector<vector<int>> tabuList = {solution};
    bool betterSolutionIsFound;
    int tabuListOffset = 1;
    srand((unsigned) time(NULL));

    for (int i = 0; i < iterations; ++i) {
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
        cout  << "Amounts of bins in this run: " << amountOfBins << endl << "Amounts of bins in best run: "
        << lowestAmountOfBins << endl << "Iterations: " << i << endl;
    }
}