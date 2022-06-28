#include "data.h"
#include <random>
#include <algorithm>

using namespace std;

vector<int> fitness(vector<vector<int>> candidates){
    vector<int> score;
    int value = 0;
    float finalScore;
    for(int k=0; k < candidates.size(); k++){
        finalScore = 0;
        for (int i = 0; i < 8; ++i) {
            if(candidates[k][i] == 1){
                value += 1;
            }
        }
        finalScore = (value*100)/8;
        score.push_back(finalScore);
    }

    return score;
}

vector<vector<int>> candidatesForParent(){
    vector<vector<int>> candidates;
    vector<int> chromosomes;
    int randomChromosome;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 9);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            randomChromosome = distrib(gen);
            chromosomes.push_back(randomChromosome);
        }
        candidates.push_back(chromosomes);
        chromosomes.clear();
    }
    return candidates;
}

vector<vector<int>> roulette(vector<int> candidatesScores, int sumOfFitness, vector<vector<int>> candidates) {
    vector<vector<int>> choosen;
    vector<int> temp;
    for (int j = 0; j < 2; j++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, sumOfFitness);
        int random1 = distrib(gen);
        int z = 0;
        while (random1 > 0) {
            random1 = random1 - candidatesScores[z];
            if (random1 > 0) {
                z++;
            }
        }
        for (int i = 0; i < 8; i++) {
            temp.push_back(candidates[z][i]);
        }
        choosen.push_back(temp);
        temp.clear();
    }
    return choosen;
}

vector<vector<int>> tournament(vector<int> candidatesScores, vector<vector<int>> choosen){
    vector<vector<int>> secondParent;
    vector<int> temp;
    if (candidatesScores[0] >= candidatesScores[1]) {
        for(int i = 0; i < 8; i++){
            temp.push_back(choosen[0][i]);
        }
        secondParent.push_back(temp);
    } else {
        for(int i = 0; i < 8; i++){
            temp.push_back(choosen[1][i]);
        }
        secondParent.push_back(temp);
    }
    temp.clear();
    return secondParent;
}


//vector<bool> generateChild(vector<vector<int>>, vector<int> newParent){
//
//}

vector<vector<int>> geneticDemo(vector<vector<int>> parent){
    cout << "Algorytm genetyczny na przykladzie rozmnazania sie kotow" << endl;
    cout << "Jest kot o nastepujacym zestawie genow: ";
    for (int i = 0; i < parent.size(); i++){
        cout << parent[0][i] << " ";
    }
    cout << endl;
    cout << "Przyjmujemy, ze najlepszy zestaw genow to: '11111111'" << endl;
    vector<int> scoreFirstParent = fitness(parent);
    cout << "Ten zestaw genow w porownaniu do idealnego zestawu zgadza sie w " << scoreFirstParent[0] << "%" << endl;
    cout << "Do miana drugiego rodzica kandyduja 3 inne koty o genach: ";

    vector<vector<int>> candidates = candidatesForParent();
    for (auto & i : candidates) {
        for (int j = 0; j < i.size(); j++)
            cout << i[j];
        cout << endl;
    }

    cout << "Teraz nastepuje walka o mozliwosc bycia rodzicem, im lepsze geny ma kot, tym ma wieksza szanse" << endl;
    vector<int> candidatesScores = fitness(candidates);
    int sumOfFitness = 0;
    for (int fitnes: candidatesScores) {
        sumOfFitness += fitnes;
    }
    vector<vector<int>> choosen;
    choosen = roulette(candidatesScores, sumOfFitness, candidates);
    vector<int> choosenCandidatesScores = fitness(choosen);
    vector<vector<int>> winner;
    winner = tournament(candidatesScores, choosen);

    for(int j = 0; j < 8; j++){
        cout << winner[0][j] << " ";
    }

}