#include "data.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<vector<bool>> generatePopulation(int populationSize, int dataSize){
    vector<vector<bool>> population;
    vector<bool> binary;
    bool randomBit;
    srand(time(NULL));
    for(int i=0; i<populationSize; i++) {
        for (int j = 0; j < dataSize; j++) {
            randomBit = rand() % 2;
            binary.push_back(randomBit);
        }
        population.push_back(binary);
        binary.clear();
    }
    return population;
}

vector<pair<int,int>> genetic(vector<pair<int, int>> data, int backpackSize, int populationSize, string crossing,
                              string mutation, string ending, int generations) {
    //generate chromosomes
    shuffle(begin(data), end(data), mt19937(random_device()()));
    vector<vector<bool>> population;
    population = generatePopulation(populationSize, data.size());

    //show data
//    cout << "dane" << endl;
//    for(int i = 0; i < data.size(); i++)
//    {
//        cout << data[i].first << ", " << data[i].second << endl;
//    }

    //show population
//    cout << "populacja" << endl;
//    for (auto & i : population) {
//        for (int j = 0; j < i.size(); j++)
//            cout << i[j] << " ";
//        cout << endl;
//    }

    //show scores
//    cout << "scores" << endl;
//    for(auto i: scores){
//        cout << i << endl;
//    }

    vector<vector<bool>> children;
    int iterations = 0;

    if (ending == "generations") {
        do {
            //scores
            vector<int> scores = fitness(populationSize, data, backpackSize, population);

            int sumOfFitness = 0;
            for (int fitnes: scores) {
                sumOfFitness += fitnes;
            }

            for (int p = 0; p < populationSize / 2; p++) {
                vector<int> contestantFitness;
                vector<int> contestant;
                vector<int> parent;

                //roulette
                for (int j = 0; j < 4; j++) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, sumOfFitness);
                    int random1 = distrib(gen);
                    int z = 0;
                    while (random1 > 0) {
                        random1 = random1 - scores[z];
                        if (random1 > 0) {
                            z++;
                        }
                    }
                    contestantFitness.push_back(scores[z]);
                    contestant.push_back(z);
                }

//                cout << "contestantFitness" << endl;
//                for(auto c: contestantFitness){
//                    cout << c << endl;
//                }
//
//                cout << "contestant" << endl;
//                for(auto d: contestant){
//                    cout << d << endl;
//                }

                //tournament
                parent = genetic_tournament(contestant, contestantFitness, parent);

                //show winners
//                cout << "winners" << endl;
//                for(auto d: parent){
//                    cout << d << endl;
//                }
//
//                cout << "parents" << endl;
//                for(int i : parent){
//                    for(int j = 0; j < data.size(); j++){
//                        cout << population[i][j] << " ";
//                    }
//                    cout << endl;
//                }

                //crossing
                children = genetic_crossing(crossing, parent, population, children, data);

                //show children
//                cout << "children" << endl;
//                for (auto & i : children) {
//                    for (int j = 0; j < data.size(); j++)
//                        cout << i[j] << " ";
//                    cout << endl;
//                }

                contestant.clear();
                contestantFitness.clear();

                //mutation
                children = genetic_mutation(children, mutation, data);

                //show new children
//                cout << "new children" << endl;
//                for (auto & i : children) {
//                    for (int j = 0; j < data.size(); j++)
//                        cout << i[j] << " ";
//                    cout << endl;
//                }
            }
            iterations++;
            population = children;
            children.clear();
            //cout << iterations << endl;

        } while (iterations < generations);
        vector<int> newGeneration = fitness(populationSize, data, backpackSize, population);

        //show children fitness
//    cout << "children fitness" << endl;
//    for(auto d: newGeneration){
//        cout << d << endl;
//    }

        int best = newGeneration[0];
        int bestIndex;

        for (int i = 0; i < populationSize; i++) {
            if (newGeneration[i] > best) {
                best = newGeneration[i];
                bestIndex = i;
            }
        }

        cout << "Wartosc plecaka: " << best << endl;
        //cout << bestIndex << endl;

        for (int i = 0; i < population.size(); i++) {
            if (population[bestIndex][i]) {
                cout << "Rozmiar " << data[i].first << " Wartosc " << data[i].second << endl;
            }
        }
    }

//    cout << "final children" << endl;
//    for (auto & i : population) {
//        for (int j = 0; j < data.size(); j++)
//            cout << i[j] << " ";
//        cout << endl;
//    }

    if (ending == "best") {
        int bestParent;
        int bestChild;
        int bestIndexParent;
        vector<int> parent;

        do {
            //scores
            vector<int> scores = fitness(populationSize, data, backpackSize, population);

            int sumOfFitness = 0;
            for (int fitnes: scores) {
                sumOfFitness += fitnes;
            }

            for (int p = 0; p < populationSize / 2; p++) {
                vector<int> contestantFitness;
                vector<int> contestant;

                //roulette
                for (int j = 0; j < 4; j++) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, sumOfFitness);
                    int random1 = distrib(gen);
                    int z = 0;
                    while (random1 > 0) {
                        random1 = random1 - scores[z];
                        if (random1 > 0) {
                            z++;
                        }
                    }
                    contestantFitness.push_back(scores[z]);
                    contestant.push_back(z);
                }

                //tournament
                parent = genetic_tournament(contestant, contestantFitness, parent);

                //crossing
                children = genetic_crossing(crossing, parent, population, children, data);

                contestant.clear();
                contestantFitness.clear();

                //mutation
                children = genetic_mutation(children, mutation, data);
            }

            vector<int> newGeneration = fitness(populationSize, data, backpackSize, children);
            
            bestParent = scores[0];
            bestChild = newGeneration[0];

            for (int i = 0; i < populationSize; i++) {
                if (scores[i] > bestParent) {
                    bestParent = scores[i];
                    bestIndexParent = i;
                }
            }

            for (int i = 0; i < populationSize; i++) {
                if (newGeneration[i] > bestChild) {
                    bestChild = newGeneration[i];
                }
            }

            //cout << bestParent << " " << bestChild << endl;

            if (bestParent <= bestChild) {
                population = children;
                children.clear();
            }


        } while (bestChild >= bestParent);

        cout << "Wartosc plecaka: " << bestParent << endl;
        //cout << bestIndex << endl;

        for (int i = 0; i < population.size(); i++) {
            if (population[bestIndexParent][i]) {
                cout << "Rozmiar " << data[i].first << " Wartosc " << data[i].second << endl;
            }
        }
    }
}