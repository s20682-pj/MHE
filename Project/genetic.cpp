#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<vector<bool>> generatePopulation(int populationSize, int dataSize){
    vector<vector<bool>> population;
    vector<bool> binary;
    bool randomBit;
    for(int i=0; i<pow(2,populationSize); i++) {
        for (int j = 0; j < populationSize; j++) {
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

    //show data
    cout << "dane" << endl;
    for(int i = 0; i < populationSize; i++)
    {
        cout << data[i].first << ", " << data[i].second << endl;
    }


    //fitness
    for(int k=0; k<pow(2,populationSize);k++){
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

    //show population
    cout << "populacja" << endl;
    for (int i = 0; i < population.size(); i++) {
        for (int j = 0; j < population[i].size(); j++)
            cout << population[i][j] << " ";
        cout << endl;
    }

    //show fitness
    cout << "fitness" << endl;
    for(auto i: fitness){
        cout << i << endl;
    }

    //roulette
    int sumOfFitness = 0;
    for(int fitnes : fitness){
        sumOfFitness += fitnes;
    }


    vector<int> contestantFitness;
    vector<bool> contestant;
    vector<int> parent;

 //   for(int i=0; i < populationSize; i++){

        for(int j=0; j < 2; j++){
            int random1 = rand() % sumOfFitness;
            int z = 1;
            do {
                random1 = random1 - fitness[z];
                z++;
            } while (random1 > 0);
            contestantFitness.push_back(fitness[z]);
            contestant.push_back(z);
        }

//        for(auto c: contestantFitness){
//            cout << c << endl;
//        }
//
//        for(auto d: contestant){
//            cout << d << endl;
//        }


        if(contestantFitness[1] >= contestantFitness[2]){
            parent.push_back(contestant[1]);
        }else parent.push_back(contestant[2]);

        vector<vector<bool>> children;


//        for(int l = 0; l < populationSize/2; l++){
//            children.push_back(population[parent[1]][l]);
//        }

        contestant.clear();
        contestantFitness.clear();

 //   }



}
