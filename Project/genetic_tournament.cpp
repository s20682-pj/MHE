#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<int> genetic_tournament(vector<int> contestant, vector<int> contestantFitness, vector<int> parent){
    int random2 = 0;
    int random3 = 0;
    for (int i = 0; i < 2; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, contestant.size() - 1);
        random2 = distrib(gen);
        random3 = distrib(gen);
        while (random2 == random3) {
            random3 = distrib(gen);
        }
        if (contestantFitness[random2] >= contestantFitness[random3]) {
            parent.push_back(contestant[random2]);
        } else parent.push_back(contestant[random3]);
//                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random2]));
//                    contestant.erase(find(contestant.begin(), contestant.end(), contestant[random3]));
//                    contestantFitness.erase(
//                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random2]));
//                    contestantFitness.erase(
//                            find(contestantFitness.begin(), contestantFitness.end(), contestantFitness[random3]));
    }
    return parent;
}
