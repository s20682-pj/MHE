#include "data.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

vector<vector<bool>> generatePopulation(int populationSize, int dataSize) {
    vector<vector<bool>> population;
    vector<bool> binary;
    bool randomBit;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < dataSize; j++) {
            randomBit = distrib(gen);
            binary.push_back(randomBit);
        }
        population.push_back(binary);
        binary.clear();
    }
    return population;
}

vector<vector<bool>> genetic(vector<pair<int, int>> data, int backpackSize, int populationSize, const string &crossing,
                             const string &mutation, const string &ending, int generations, int ifScript, int howLong) {
    clock_t start = clock();

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
//                -
//
//              cout << "contestant" << endl;
//                for(auto d: contestant){
//                    cout << d;
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

            //cout << iterations << endl;
            if (ifScript){
                vector<int> tmpScores = fitness(populationSize, data, backpackSize, children);
                int best = tmpScores[0];
                for (int i = 0; i < populationSize-1; i++) {
                    if (children[i] > children[i+1]) {
                        best = tmpScores[i];
                        i++;
                    }
                }
                ofstream myfile;
                myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/resultGenetic.txt", fstream::app);
                myfile << iterations << "," << best << endl;
                myfile.close();
            }

            iterations++;
            population = children;
            children.clear();

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

        clock_t finish = clock();
        if(howLong){
            double elapsed = double(finish - start)/CLOCKS_PER_SEC;
            ofstream myfile;
            myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/result.txt", fstream::app);
            myfile << "GG," << elapsed << endl;
            myfile.close();
        }

        if (ifScript != 1 and howLong != 1){
            cout << "Wartosc plecaka: " << best << endl;
            //cout << bestIndex << endl;

            for (int i = 0; i < population.size(); i++) {
                if (population[bestIndex][i]) {
                    cout << "Rozmiar " << data[i].first << " Wartosc " << data[i].second << endl;
                }
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

        clock_t finish = clock();
        if(howLong){
            double elapsed = double(finish - start)/CLOCKS_PER_SEC;
            ofstream myfile;
            myfile.open ("C:/Users/Zazu/Desktop/studia/sem6/MHE/KnapsackProblem/Scripts/result.txt", fstream::app);
            myfile << "GB," << elapsed << endl;
            myfile.close();
        }

        //cout << bestIndex << endl;

        if (ifScript != 1 and howLong != 1){
            cout << "Wartosc plecaka: " << bestParent << endl;
            for (int i = 0; i < population.size(); i++) {
                if (population[bestIndexParent][i]) {
                    cout << "Rozmiar " << data[i].first << " Wartosc " << data[i].second << endl;
                }
            }
        }
    }
    return population;
}