#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

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