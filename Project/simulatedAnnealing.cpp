#include "data.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;
vector<pair<int,int>> simulatedAnnealing(vector<pair<int, int>> data, int backpackSize, int iterations,
                                         bool uniformRealDistributionIsSet, int ifScript, int howLong) {
    clock_t start = clock();

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int nextResult, bestScore;
    double boltzmannDistribution;
    vector<pair<int, int>> bestSolution = data;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> uniformRealDistribution(0.0, 1.0);
    normal_distribution<double> normalDistribution(0.5,0.25);
    int iteration_counter;

    for (iteration_counter = 0; iteration_counter < iterations; iteration_counter++) {
        shuffle(begin(data), end(data), mt19937(random_device()()));
        vector<pair<int, int>> nextSolution = data;
        nextResult = knapsack(nextSolution, backpackSize);
        boltzmannDistribution = exp(-abs(score - nextResult) / (iterations / (iteration_counter + 1)));
        if (nextResult > score ){
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

        if (ifScript){
            ofstream myfile;
            myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/resultSimulatedAnnealing.txt", fstream::app);
            myfile << iteration_counter << "," << bestScore << endl;
            myfile.close();
        }
    }
    clock_t finish = clock();
    if(howLong){
        double elapsed = double(finish - start)/CLOCKS_PER_SEC;
        ofstream myfile;
        myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/result.txt", fstream::app);
        myfile << "SA," << elapsed << endl;
        myfile.close();
    }

    if (ifScript != 1 && howLong != 1) {
        cout << "Wartosc plecaka: " << score << endl;

        int tmp = 0;

        cout << "Przedmioty: " << endl;
        for (int j = 0; tmp < score; j++) {
            tmp = tmp + data[j].second;
            cout << data[j].first << " " << data[j].second << endl;
        }

    }
    return bestSolution;
}
