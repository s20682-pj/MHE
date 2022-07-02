#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<vector<bool>> genetic_mutation(vector<vector<bool>> children, string mutation, vector<pair<int, int>> data){
    if (mutation == "random") {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 1);
        uniform_int_distribution<> distrib2(0, data.size()-1);
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
    return children;
}
