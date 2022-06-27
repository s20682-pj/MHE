#include <vector>
#include <iostream>
#include <complex>
#include <any>
#include <fstream>

#include "data.h"

using namespace std;
vector<pair<int, int>> loadProblem(string fname){
    vector<pair<int, int>> v;
    pair<int, int> vv;
    fstream file;
    file.open(fname);
    stringstream ss;
    string tmp;
    int x,y = 0;
    if(file.is_open()){
        while(!file.eof()){
            getline(file, tmp, ';');
            ss.str(tmp);
            ss >> x;
            ss.clear();
            getline(file, tmp);
            ss.str(tmp);
            ss >> y;
            ss.clear();
            vv = {x, y};
            v.push_back(vv);
        }
        file.close();
    }
    return v;
}

auto args = [](int argc, char** argv, string name, auto default_value) -> decltype(default_value) {
    string paramname = "";
    any ret = default_value;
    for (auto argument: vector<string>(argv, argv + argc)) {
        if ((argument.size() > 0) && (argument[0] == '-')) {
            if (paramname != "") {
                if (name == argument.substr(1)) ret = true;
            }
            paramname = argument.substr(1);
        } else if (name == paramname) {
            if (is_same_v<decltype(default_value), int>) ret = stoi(argument);
            else if (is_same_v<decltype(default_value), double>) ret = stod( argument );
            else if (is_same_v<decltype(default_value), char>) ret = argument.at(0);
            else if (is_same_v<decltype(default_value), bool>) ret = (argument=="true") || (argument=="1") || (argument=="yes");
            else ret = argument;
            paramname = "";
        }
    }
    return any_cast<decltype(default_value)>(ret);
};

int main(int argc, char **argv) {
cout << "hello world";
    auto fname = args(argc, argv, "fname", string(""));
    auto iterations = args(argc, argv, "iterations", 1000);
    auto method = args(argc, argv, "method", string("hc"));
    auto tabu_size = args(argc, argv, "tabu_size", 100);
    auto backpackSize = args(argc, argv, "backpackSize", 30);
    auto uniformRealDistributionIsSet = args(argc, argv, "uniformRealDistributionIsSet", true);
    auto crossing = args(argc, argv, "crossing", string("half"));
    auto populationSize = args(argc, argv, "populationSize", 16);
    auto mutation = args(argc, argv, "mutation", string("random"));
    auto ending = args(argc, argv, "ending", string("generations"));
    auto generations = args(argc, argv, "generations", 1);
    auto ifScript = args(argc, argv, "script", 0);

    vector<pair<int, int>> data;

    if(fname==""){
        cout<<"Enter size and press enter"<<endl;
        vector <pair<int, int>> trash;
        int temp1;
        int temp2;
        while(cin >> temp1, temp2){
            trash.emplace_back(temp1, temp2);
        }
    } else{
        data = loadProblem(fname);
    }

    if (method == "hc") {
        hillClimbing(data, backpackSize, iterations, ifScript);
    } else if (method == "random") {
        hillClimbingRandom(data, backpackSize, iterations, ifScript);
    } else if (method == "tabu") {
        tabuSearch(data, backpackSize, tabu_size, iterations, ifScript);
    } else if (method == "sa") {
        simulatedAnnealing(data, backpackSize, iterations, uniformRealDistributionIsSet, ifScript);
    }
    else if (method == "genetic"){
        genetic(data, backpackSize, populationSize, crossing, mutation, ending, generations);
    }

    return 0;

}