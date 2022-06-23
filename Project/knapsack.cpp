#include <vector>

using namespace std;
int knapsack(vector<pair<int, int>> data, int backpackSize) {
    int sumInBackpack = 0;
    int valueInBackpack = 0;

    for (int i = 0; i < data.size(); ++i) {
        int size = data[i].first;
        int value = data[i].second;
        if (sumInBackpack + size <= backpackSize){
            sumInBackpack += size;
            valueInBackpack += value;
        }
    }
    return valueInBackpack;
}
