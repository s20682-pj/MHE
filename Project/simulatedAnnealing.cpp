#include "data.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;
vector<pair<int,int>> simulatedAnnealing(vector<pair<int, int>> data, int backpackSize, int iterations,
                                         bool uniformRealDistributionIsSet, int ifScript, int howLong) {
    struct timeval start, finish;
    mingw_gettimeofday(&start, 0);

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int nextResult, bestScore;
    double boltzmannDistribution;
    vector<pair<int, int>> bestSolution = data;
    vector<pair<int, int>> nextSolution = data;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> uniformRealDistribution(0.0, 1.0);
    normal_distribution<double> normalDistribution(0.5,0.25);
    int iteration_counter;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        shuffle(begin(nextSolution), end(nextSolution), gen);
        nextResult = knapsack(nextSolution, backpackSize);
        boltzmannDistribution = exp(-abs(score - nextResult) / (iterations / (iteration_counter + 1)));
        if (nextResult < score ){
            data = nextSolution;
            score = nextResult;
            //rozkład liniowy
        } else if (uniformRealDistributionIsSet && (uniformRealDistribution(gen) < boltzmannDistribution)) {
            data = nextSolution;
            score = nextResult;
            //rozkład normalny
        } else if (!uniformRealDistributionIsSet && (normalDistribution(gen) < boltzmannDistribution)) {
            data = nextSolution;
            score = nextResult;
        }
        bestScore = knapsack(bestSolution, backpackSize);
        if (score > bestScore){
            bestSolution = data;
            bestScore = score;
        }
        if (ifScript) cout << iteration_counter << " " << bestScore << endl;
    }
    mingw_gettimeofday(&finish, 0);
    if(howLong){
        long seconds = finish.tv_sec - start.tv_sec;
        long microseconds = finish.tv_usec - start.tv_usec;
        double elapsed = seconds + microseconds*1e-6;
        cout << elapsed;
    }

    if (ifScript != 1 and howLong != 1) {
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