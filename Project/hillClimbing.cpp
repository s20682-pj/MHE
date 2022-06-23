#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;
vector<pair<int,int>> hillClimbing(vector<pair<int, int>> data, int backpackSize, int iterations) {

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int bestScore = score;
    int iteration_counter;

    srand((unsigned) time(NULL));

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        for (int i = 0; i < data.size(); ++i) {
            swap(data[i], data[i+1]);
            score = knapsack(data, backpackSize);
            if (score < bestScore) {
                bestScore = score;
            }
        }
    }
    cout << "Value in the backpack: " << bestScore << endl << "Iterations: " << iteration_counter << endl;

}

vector<pair<int,int>> hillClimbingRandom(vector<pair<int, int>> data, int binSize, int iterations) {
    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, binSize);
    int iteration_counter;
    int newScore;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        int x = rand() % (end(data) - begin(data));
        for (int j = 0; j < data.size(); ++j) {
            swap(data[x], data[j]);
            newScore = knapsack(data, binSize);
            if (newScore < score) {
                score = newScore;
            }
    }}
    cout << "Value in the backpack: " << score << endl << "Iterations: " << iteration_counter << endl;
}