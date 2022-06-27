#include "data.h"
#include <list>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;
vector<pair<int,int>> tabuSearch(vector<pair<int, int>> data, int backpackSize, int tabu_size, int iterations, int ifScript, int howLong){
    clock_t start = clock();

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int bestScore = score;
    vector<pair<int, int>> bestSolution = data;
    vector<vector<pair<int, int>>> tabuList = {data};
    bool betterSolutionIsFound;
    int tabuListOffset = 1;
    int iteration_counter;
    srand((unsigned) time(NULL));

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        betterSolutionIsFound = false;
        int x = rand() % (end(data) - begin(data));
        for (int j = 0; j < data.size(); ++j) {
            swap(data[x], data[j]);
            score = knapsack(data, backpackSize);
            bool isNotInTabu = find(tabuList.begin(), tabuList.end(), data) == tabuList.end();
            if (score >= bestScore and  isNotInTabu){
                bestScore = score;
                bestSolution = data;
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
            data = tabuList[tabuList.size() - tabuListOffset];
            tabuListOffset++;
        }
        else{
            break;
        }
        if (ifScript) cout << iteration_counter << " " << bestScore << endl;
    }
    clock_t finish = clock();
    if(howLong){
        double elapsed = double(finish - start)/CLOCKS_PER_SEC;
        cout  << "Tabu " << elapsed << endl;
    }

    if (ifScript != 1 and howLong !=1) {
        cout << "Wartosc plecaka: " << bestScore << endl;

        int tmp = 0;

        cout << "Przedmioty: " << endl;
        for (int j = 0; tmp < bestScore; j++) {
            tmp = tmp + data[j].second;
            cout << data[j].first << " " << data[j].second << endl;
        }

    }
    return bestSolution;
}
