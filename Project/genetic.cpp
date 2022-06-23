#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<vector<bool>> generatePopulation(int populationSize, int dataSize){
    vector<vector<bool>> population;
    vector<bool> binary;
    bool randomBit;
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

vector<pair<int,int>> genetic(vector<pair<int, int>> data, int backpackSize, int iterations, int populationSize){
    //generate chromosomes
    shuffle(begin(data), end(data), mt19937(random_device()()));
    vector<vector<bool>> population;
    population = generatePopulation(populationSize, data.size());
    vector<int> fitness;

    //fitness
    for(int k=0; k<populationSize;k++){
        int sumInBackpack = 0;
        int valueInBackpack = 0;
        for (int i = 0; i < data.size(); ++i) {
            if(population[k][i]){
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
        fitness.push_back(valueInBackpack);
    }

//    for(auto i: fitness){
//            cout << i << ", ";
//        }

    //roulette
    int sumOfFitness = 0;
    for(int i=0; i<fitness.size(); i++){
        sumOfFitness += fitness[i];
    }

    int random = rand() % sumOfFitness;
    int i = 0;
    do {
        random = random - fitness[i];
        i++;
    } while (random > 0);

    cout << i << " " << population[i][i] << " " << fitness[i];
//
//    //tournament
//    for()
}
