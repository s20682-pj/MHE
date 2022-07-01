#include "data.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

vector<pair<int, int>> hillClimbing(vector<pair<int, int>> data, int backpackSize, int ifScript, int howLong) {
    clock_t start = clock();

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, backpackSize);
    int bestScore = score;
    vector<pair<int, int>> bestSolution = data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, data.size()-1);
    int x = distrib(gen);
    bool isBetter = true;
    int iteration = 1;

    while(isBetter){
        isBetter = false;
        for (int j = 0; j < data.size(); ++j) {
            iteration++;
            swap(data[x], data[j]);
            score = knapsack(data, backpackSize);
            if (score > bestScore) {
                bestScore = score;
                bestSolution = data;
                isBetter = true;
                if(ifScript){
                    ofstream myfile;
                    myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/resultHillClimbing.txt", fstream::app);
                    myfile << iteration << "," << bestScore << endl;
                    myfile.close();
                }
            } else{
                swap(data[x], data[j]);
            }
        }
        if(isBetter){
            data = bestSolution;
            x=0;
        } else if(x < data.size() - 1) {
            x++;
        } else {
            isBetter = false;
        }


    }

    clock_t finish = clock();
    if(howLong){
        double elapsed = double(finish - start)/CLOCKS_PER_SEC;
        ofstream myfile;
        myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/result.txt", fstream::app);
        myfile << "HC," << elapsed << endl;
        myfile.close();
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
    clock_t start = clock();

    shuffle(begin(data), end(data), mt19937(random_device()()));
    int score = knapsack(data, binSize);
    int iteration_counter;
    int newScore;
    vector<pair<int, int>> bestSolution = data;

    for (iteration_counter = 0; iteration_counter < iterations; ++iteration_counter) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, data.size()-1);
        int x = distrib(gen);
        for (int j = 0; j < data.size(); ++j) {
            swap(data[x], data[j]);
            newScore = knapsack(data, binSize);
            if (newScore > score) {
                score = newScore;
                bestSolution = data;
            } else swap(data[j], data[x]);
        }
        if (ifScript){
            ofstream myfile;
            myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/resultRandomHillClimbing.txt", fstream::app);
            myfile << iteration_counter << "," << score << endl;
            myfile.close();
        }
    }
    clock_t finish = clock();
    if(howLong){
        double elapsed = double(finish - start)/CLOCKS_PER_SEC;
        ofstream myfile;
        myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/result.txt", fstream::app);
        myfile << "HCR," << elapsed << endl;
        myfile.close();
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