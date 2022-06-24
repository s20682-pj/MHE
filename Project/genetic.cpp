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
    for(int k=0; k < populationSize;k++){
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

vector<pair<int,int>> genetic(vector<pair<int, int>> data, int backpackSize, int iterations, int populationSize){
    //generate chromosomes
    shuffle(begin(data), end(data), mt19937(random_device()()));
    vector<vector<bool>> population;
    population = generatePopulation(populationSize, data.size());


    //show data
    cout << "dane" << endl;
    for(int i = 0; i < populationSize; i++)
    {
        cout << data[i].first << ", " << data[i].second << endl;
    }


    //scores
    vector<int> scores = fitness(populationSize, data, backpackSize, population);
//    for(int k=0; k<pow(2,populationSize);k++){
//        int sumInBackpack = 0;
//        int valueInBackpack = 0;
//        for (int i = 0; i < data.size(); ++i) {
//            if(population[k][i] and i < populationSize){
//                int size = data[i].first;
//                int value = data[i].second;
//                if (sumInBackpack + size <= backpackSize){
//                    sumInBackpack += size;
//                    valueInBackpack += value;
//                }else if (sumInBackpack + size > backpackSize) {
//                    valueInBackpack = 0;
//                    break;
//                }
//            }
//        }
//        scores.push_back(valueInBackpack);
//    }

    //show population
    cout << "populacja" << endl;
    for (auto & i : population) {
        for (int j = 0; j < i.size(); j++)
            cout << i[j] << " ";
        cout << endl;
    }

    //show scores
    cout << "scores" << endl;
    for(auto i: scores){
        cout << i << endl;
    }

    //roulette
    int sumOfFitness = 0;
    for(int fitnes : scores){
        sumOfFitness += fitnes;
    }


    vector<int> contestantFitness;
    vector<int> contestant;
    vector<vector<bool>> children;

    for(int p=0; p < populationSize/2; p++){


        for(int j=0; j < 4; j++){
            int random1 = rand() % sumOfFitness;
            int z = 0;
            while(random1 > 0) {

                random1 = random1 - scores[z];
                if(random1 > 0){
                    z++;
                }

            }

            contestantFitness.push_back(scores[z]);
            contestant.push_back(z);

        }

        cout << "contestantFitness" << endl;
        for(auto c: contestantFitness){
            cout << c << endl;
        }

        cout << "contestant" << endl;
        for(auto d: contestant){
            cout << d << endl;
        }

        vector<int> parent;
        int random2 = 0;
        int random3 = 0;

        //tournament
        for(int i=0; i < 2; i++){
            srand(time(NULL));
            random2 = rand() % contestant.size();
            random3 = rand() % contestant.size();
            if(contestantFitness[random2] >= contestantFitness[random3]){
                parent.push_back(contestant[random2]);
            }else parent.push_back(contestant[random3]);
            contestant.erase(find(contestant.begin(),contestant.end(),contestant[random2]));
            contestant.erase(find(contestant.begin(),contestant.end(),contestant[random3]));
            contestantFitness.erase(find(contestantFitness.begin(),contestantFitness.end(),contestantFitness[random2]));
            contestantFitness.erase(find(contestantFitness.begin(),contestantFitness.end(),contestantFitness[random3]));
        }


        //show winners
        cout << "winners" << endl;
        for(auto d: parent){
            cout << d << endl;
        }


        //crossing



//        for(int l = 0; l < populationSize/2; l++){
//            children.push_back(population[parent[1]][l]);
//        }

        bool chromosome;
        vector<bool> childrentmp;

        cout << "parents" << endl;
        for(int i = 0; i < parent.size(); i++){
            for(int j = 0; j < data.size(); j++){
                cout << population[parent[i]][j];
            }
            cout << endl;
        }

        int halfData = data.size()/2;



        for (int j = 0; j < halfData; j++) {
            chromosome = population[parent[0]][j];
            childrentmp.push_back(chromosome);
        }
        for (int j = halfData; j < populationSize; j++) {
            chromosome = population[parent[1]][j];
            childrentmp.push_back(chromosome);
        }
        children.push_back(childrentmp);
        childrentmp.clear();


        for (int j = 0; j < halfData; j++) {
            chromosome = population[parent[1]][j];
            childrentmp.push_back(chromosome);
        }
        for (int j = halfData; j < populationSize; j++) {
            chromosome = population[parent[0]][j];
            childrentmp.push_back(chromosome);
        }
        children.insert(children.begin(), childrentmp);
        childrentmp.clear();





        //show children
        cout << "children" << endl;
        for (auto & i : children) {
            for (int j = 0; j < data.size(); j++)
                cout << i[j] << " ";
            cout << endl;
        }

        contestant.clear();
        contestantFitness.clear();


        //mutation
        int random4 = rand() % 1;
        int random5 =  rand() % populationSize;
        if(children[random4][random5]){
            children[random4][random5] = false;
        }else children[random4][random5] = true;

        //show new children
        cout << "new children" << endl;
        for (auto & i : children) {
            for (int j = 0; j < data.size(); j++)
                cout << i[j] << " ";
            cout << endl;
        }
    }

    cout << "final children" << endl;
    for (auto & i : children) {
        for (int j = 0; j < data.size(); j++)
            cout << i[j] << " ";
        cout << endl;
    }



    vector<int> childrenScores = fitness(populationSize, data, backpackSize, children);
    //show children fitness
    cout << "children fitness" << endl;
    for(auto d: childrenScores){
        cout << d << endl;
    }


}
