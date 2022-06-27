#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

vector<pair<int, int>> hillClimbing(vector<pair<int, int>> data, int backpackSize, int iterations, int ifScript, int howLong) {
    time_t start, finish;
    time(&start);

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int bestScore = score;
    int iteration_counter;
    vector<pair<int, int>> bestSolution = data;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        int x = rand() % (end(data) - begin(data));
        for (int i = 0; i < data.size(); ++i) {
            swap(data[x], data[i]);
            score = knapsack(data, backpackSize);
            if (score > bestScore) {
                bestScore = score;
                bestSolution = data;
            } else swap(data[i + 1], data[i]);
        }
        if (ifScript) cout << iteration_counter << " " << bestScore << endl;
    }

    time(&finish);
    if(howLong){
        time_t elapsed = finish - start;
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

vector<pair<int, int>> hillClimbingRandom(vector<pair<int, int>> data, int binSize, int iterations, int ifScript, int howLong) {
    time_t start, finish;
    time(&start);

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, binSize);
    int iteration_counter;
    int newScore;
    vector<pair<int, int>> bestSolution = data;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        int x = rand() % (end(data) - begin(data));
        for (int j = 0; j < data.size(); ++j) {
            swap(data[x], data[j]);
            newScore = knapsack(data, binSize);
            if (newScore > score) {
                score = newScore;
                bestSolution = data;
            } else swap(data[j], data[x]);
        }
        if (ifScript) cout << iteration_counter << " " << score << endl;
    }
    time(&finish);
    if(howLong){
        time_t elapsed = finish - start;
        cout << elapsed;
    }

    if (ifScript != 1 and howLong !=1) {
        cout << "Wartosc plecaka: " << newScore << endl;

        int tmp = 0;

        cout << "Przedmioty: " << endl;
        for (int j = 0; tmp < newScore; j++) {
            tmp = tmp + data[j].second;
            cout << data[j].first << " " << data[j].second << endl;
        }

    }
    return bestSolution;
}