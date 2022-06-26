#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<vector<bool>> genetic_crossing(string crossing, vector<int> parent, vector<vector<bool>> population, vector<vector<bool>> children,
                                      vector<pair<int, int>> data){
    bool chromosome;
    vector<bool> childrentmp;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, data.size() - 2);
    int halfData = distrib(gen);
    //cout << halfData << endl;
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
        for (int i = 0; i < data.size(); i++) {
            chromosome = population[parent[0]][i];
            childrentmp.push_back(chromosome);
            i++;
            chromosome = population[parent[1]][i];
            childrentmp.push_back(chromosome);
        }
        children.insert(children.begin(), childrentmp);
        childrentmp.clear();
        for (int i = 0; i < data.size(); i++) {
            chromosome = population[parent[1]][i];
            childrentmp.push_back(chromosome);
            i++;
            chromosome = population[parent[0]][i];
            childrentmp.push_back(chromosome);
        }
        children.insert(children.begin(), childrentmp);
        childrentmp.clear();

    }
    childrentmp.clear();
    parent.clear();
    return children;
}