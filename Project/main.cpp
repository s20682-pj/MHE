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

    auto fname = args(argc, argv, "fname", string(""));
    auto iterations = args(argc, argv, "iterations", 1000);
    auto method = args(argc, argv, "method", string("hc"));
    auto tabu_size = args(argc, argv, "tabu_size", 100);
    auto quantity = args(argc, argv, "quantity", 10);
    auto backpackSize = args(argc, argv, "backpackSize", 15);
    auto uniformRealDistributionIsSet = args(argc, argv, "uniformRealDistributionIsSet", false);
    auto showBestOrAll = args(argc, argv, "showBestOrAll", string("best"));
    auto crossing = args(argc, argv, "crossing", string("random"));

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
        hillClimbing(data, backpackSize, iterations);
    } else if (method == "random") {
        hillClimbingRandom(data, backpackSize, iterations);
//    } else if (method == "tabu") {
//        tabuSearch(data, binSize, quantity, tabu_size, iterations, showBestOrAll);
//    } else if (method == "sa") {
//        simulatedAnnealing(data, binSize, quantity, iterations, uniformRealDistributionIsSet, showBestOrAll);

    }
    else if (method == "genetic"){
        genetic(data, backpackSize, iterations, 4);
    }

    return 0;

}