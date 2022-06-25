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

vector<int> fitness(int populationSize, vector<pair<int, int>> data, int backpackSize, vector<vector<bool>> population){
    vector<int> score;
    for(int k=0; k < populationSize; k++){
        int sumInBackpack = 0;
        int valueInBackpack = 0;
        for (int i = 0; i < data.size(); ++i) {
            if(population[k][i] and i < populationSize){
                int size = data[i].first;
                int value = data[i].second;
                if (sumInBackpack + size <= backpackSize){
                    sumInBackpack += size;
                    valueInBackpack += value;
                }else if (sumInBackpack + size > backpackSize) {
                    valueInBackpack = 0;
                    break;
                }
            }
        }
        score.push_back(valueInBackpack);
    }
    return score;
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

                vector<int> parent;
                int random2 = 0;
                int random3 = 0;

                //tournament
                for (int i = 0; i < 2; i++) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, contestant.size() - 1);
                    random2 = distrib(gen);
                    random3 = distrib(gen);
                    while (random2 == random3) {
                        random3 = distrib(gen);
                    }
                    if (contestantFitness[random2] >= contestantFitness[random3]) {
                        parent.push_back(contestant[random2]);
                    } else parent.push_back(contestant[random3]);
                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random2]));
                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random3]));
                    contestantFitness.erase(
                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random2]));
                    contestantFitness.erase(
                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random3]));
                }


                //show winners
//                cout << "winners" << endl;
//                for(auto d: parent){
//                    cout << d << endl;
//                }

                bool chromosome;
                vector<bool> childrentmp;

//        cout << "parents" << endl;
//                for(int i : parent){
//                    for(int j = 0; j < data.size(); j++){
//                        cout << population[i][j] << " ";
//                    }
//                    cout << endl;
//                }

                //crossing
                int halfData = data.size() / 2;
                if (crossing == "half") {
                    for (int j = 0; j < halfData; j++) {
                        chromosome = population[parent[0]][j];
                        childrentmp.push_back(chromosome);
                    }
                    for (int j = halfData; j < data.size(); j++) {
                        chromosome = population[parent[1]][j];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();

                    for (int j = 0; j < halfData; j++) {
                        chromosome = population[parent[1]][j];
                        childrentmp.push_back(chromosome);
                    }
                    for (int j = halfData; j < data.size(); j++) {
                        chromosome = population[parent[0]][j];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();
                } else {
                    for (int i = 0; i < halfData; i++) {
                        chromosome = population[parent[0]][i];
                        childrentmp.push_back(chromosome);
                        i++;
                        chromosome = population[parent[1]][i];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();
                    for (int i = halfData; i < data.size(); i++) {
                        chromosome = population[parent[1]][i];
                        childrentmp.push_back(chromosome);
                        i++;
                        chromosome = population[parent[0]][i];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();

                }

                //show children
//                cout << "children" << endl;
//                for (auto & i : children) {
//                    for (int j = 0; j < data.size(); j++)
//                        cout << i[j] << " ";
//                    cout << endl;
//                }

                contestant.clear();
                contestantFitness.clear();
                childrentmp.clear();
                parent.clear();


                //mutation
                if (mutation == "random") {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 1);
                    uniform_int_distribution<> distrib2(0, data.size());
                    int random4 = distrib(gen);
                    int random5 = distrib2(gen);
                    if (children[random4][random5]) {
                        children[random4][random5] = false;
                    } else children[random4][random5] = true;
                } else {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 1);
                    int random4 = distrib(gen);
                    if (children[random4][0]) {
                        children[random4][0] = false;
                    } else children[random4][0] = true;
                }

//        cout << "children" << endl;
//        for (auto & i : children) {
//            for (int j = 0; j < data.size(); j++)
//                cout << i[j] << " ";
//            cout << endl;
//        }


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

//                cout << "contestantFitness" << endl;
//                for(auto c: contestantFitness){
//                    cout << c << endl;
//                }
//
//                cout << "contestant" << endl;
//                for(auto d: contestant){
//                    cout << d << endl;
//                }

                vector<int> parent;
                int random2 = 0;
                int random3 = 0;

                //tournament
                for (int i = 0; i < 2; i++) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, contestant.size() - 1);
                    random2 = distrib(gen);
                    random3 = distrib(gen);
                    while (random2 == random3) {
                        random3 = distrib(gen);
                    }
                    if (contestantFitness[random2] >= contestantFitness[random3]) {
                        parent.push_back(contestant[random2]);
                    } else parent.push_back(contestant[random3]);
                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random2]));
                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random3]));
                    contestantFitness.erase(
                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random2]));
                    contestantFitness.erase(
                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random3]));
                }

                //show winners
//                cout << "winners" << endl;
//                for(auto d: parent){
//                    cout << d << endl;
//                }

                bool chromosome;
                vector<bool> childrentmp;

//        cout << "parents" << endl;
//                for(int i : parent){
//                    for(int j = 0; j < data.size(); j++){
//                        cout << population[i][j] << " ";
//                    }
//                    cout << endl;
//                }

                //crossing
                int halfData = data.size() / 2;
                if (crossing == "half") {
                    for (int j = 0; j < halfData; j++) {
                        chromosome = population[parent[0]][j];
                        childrentmp.push_back(chromosome);
                    }
                    for (int j = halfData; j < data.size(); j++) {
                        chromosome = population[parent[1]][j];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();

                    for (int j = 0; j < halfData; j++) {
                        chromosome = population[parent[1]][j];
                        childrentmp.push_back(chromosome);
                    }
                    for (int j = halfData; j < data.size(); j++) {
                        chromosome = population[parent[0]][j];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();
                } else {
                    for (int i = 0; i < halfData; i++) {
                        chromosome = population[parent[0]][i];
                        childrentmp.push_back(chromosome);
                        i++;
                        chromosome = population[parent[1]][i];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();
                    for (int i = halfData; i < data.size(); i++) {
                        chromosome = population[parent[1]][i];
                        childrentmp.push_back(chromosome);
                        i++;
                        chromosome = population[parent[0]][i];
                        childrentmp.push_back(chromosome);
                    }
                    children.insert(children.begin(), childrentmp);
                    childrentmp.clear();

                }

                //show children
//                cout << "children" << endl;
//                for (auto & i : children) {
//                    for (int j = 0; j < data.size(); j++)
//                        cout << i[j] << " ";
//                    cout << endl;
//                }

                contestant.clear();
                contestantFitness.clear();
                childrentmp.clear();
                parent.clear();

                //mutation
                if (mutation == "random") {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 1);
                    uniform_int_distribution<> distrib2(0, data.size());
                    int random4 = distrib(gen);
                    int random5 = distrib2(gen);
                    if (children[random4][random5]) {
                        children[random4][random5] = false;
                    } else children[random4][random5] = true;
                } else {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 1);
                    int random4 = distrib(gen);
                    if (children[random4][0]) {
                        children[random4][0] = false;
                    } else children[random4][0] = true;
                }

//        cout << "children" << endl;
//        for (auto & i : children) {
//            for (int j = 0; j < data.size(); j++)
//                cout << i[j] << " ";
//            cout << endl;
//        }

                //show new children
//                cout << "new children" << endl;
//                for (auto & i : children) {
//                    for (int j = 0; j < data.size(); j++)
//                        cout << i[j] << " ";
//                    cout << endl;
//                }
            }

            vector<int> newGeneration = fitness(populationSize, data, backpackSize, children);

            //show children fitness
//    cout << "children fitness" << endl;
//    for(auto d: newGeneration){
//        cout << d << endl;
//    }

            bestParent = scores[0];
            bestChild = newGeneration[0];

            for (int i = 0; i < populationSize; i++) {
                if (scores[i] > bestParent) {
                    bestParent = scores[i];
                    bestIndexParent = i;
                }
            }

            for (int i = 0; i < populationSize; i++) {
                int bestIndexChild = 0;
                if (newGeneration[i] > bestChild) {
                    bestChild = newGeneration[i];
                    bestIndexChild = i;
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