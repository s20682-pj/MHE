#include <vector>
#include <iostream>
#include <complex>
#include <any>
#include <fstream>

#include "data.h"

using namespace std;
vector<int> loadProblem(string fname) {
    vector<int> problem;
    fstream file;
    string line;
    int x;

    file.open(fname);
    if ( file.is_open() ) {
        while ( file ) {
            getline (file, line);
            stringstream sline(line);
            sline >> x;
            problem.push_back(x);
        }
    }
    else {
        cout << "Couldn't open file\n";
    }
    file.close();

    return problem;
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
    auto method = args(argc, argv, "method", string("all"));
    auto tabu_size = args(argc, argv, "tabu_size", 100);
    auto quantity = args(argc, argv, "quantity", 500);
    auto binSize = args(argc, argv, "binSize", 15);

    vector<int> data;

    if(fname==""){
        cout<<"Wpisz rozmiar i wciśnij enter"<<endl;
        int trashSize;
        while(cin >> trashSize){
            data.push_back(trashSize);
        }
    } else{
        data = loadProblem(fname);
    }

    if (method == "all") {
        hillClimbing(data, binSize, quantity, iterations);
        hillClimbingRandom(data, binSize, quantity, iterations);
        tabuSearch(data, binSize, quantity, tabu_size, iterations);
        simulatedAnnealing(data, binSize, quantity, iterations);
    } else if (method == "hc") {
        hillClimbing(data, binSize, quantity, iterations);
    } else if (method == "random") {
        hillClimbingRandom(data, binSize, quantity, iterations);
    } else if (method == "tabu") {
        tabuSearch(data, binSize, quantity, tabu_size, iterations);
    } else if (method == "sa") {
        simulatedAnnealing(data, binSize, quantity, iterations);
    }

    return 0;


}