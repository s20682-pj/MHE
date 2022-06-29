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
        value = 0;
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


vector<vector<int>> generateChild(vector<vector<int>> winner, vector<vector<int>> parent) {
    int chromosome;
    vector<int> childrentmp;
    vector<vector<int>> child;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 6);
    int halfData = distrib(gen);
    for (int j = 0; j < halfData; j++) {
        chromosome = parent[0][j];
        childrentmp.push_back(chromosome);
    }
    for (int j = halfData; j < 8; j++) {
        chromosome = winner[0][j];
        childrentmp.push_back(chromosome);
    }
    child.push_back(childrentmp);
    childrentmp.clear();
    return child;
}

vector<vector<int>> geneticMutation(vector<vector<int>> child){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 9);
    uniform_int_distribution<> distrib2(0, 7);
    int randomChromosome = distrib(gen);
    int randomBit = distrib2(gen);
    child[0][randomBit] = randomChromosome;

    return child;
}


vector<vector<int>> geneticDemo(vector<vector<int>> parent){
    cout << "Algorytm genetyczny na przykladzie rozmnazania sie kotow" << endl;
    cout << "Jest kot o nastepujacym zestawie genow: " << endl;

    for (int i = 0; i < 8; i++){
        cout << parent[0][i];
    }

    cout << endl;
    cout << "Przyjmujemy, ze najlepszy zestaw genow to: '11111111'" << endl;

    vector<int> scoreParent = fitness(parent);

    cout << "Ten zestaw genow w porownaniu do idealnego zestawu zgadza sie w " << endl << scoreParent[0] << "%" << endl;
    cout << "Do miana drugiego rodzica kandyduja 3 inne koty o genach: " << endl;

    vector<vector<int>> candidates = candidatesForParent();

    for (auto & i : candidates) {
        for (int j = 0; j < i.size(); j++)
            cout << i[j];
        cout << endl;
    }

    cout << "Teraz nastepuje walka o mozliwosc bycia rodzicem, im lepsze geny ma kot, tym ma wieksza szanse" << endl;
    cout << "Moc genow prezentuje sie nastepujaco: " << endl;

    vector<int> candidatesScores = fitness(candidates);
    int sumOfFitness = 0;

    for(auto c: candidatesScores){
        cout << c << "%" << endl;
    }

    for (int fitnes: candidatesScores) {
        sumOfFitness += fitnes;
    }

    cout << "Zwyciesca jest: " << endl;

    vector<vector<int>> choosen;
    choosen = roulette(candidatesScores, sumOfFitness, candidates);
    vector<int> choosenCandidatesScores = fitness(choosen);
    vector<vector<int>> winner;
    winner = tournament(candidatesScores, choosen);

    for(int j = 0; j < 8; j++){
        cout << winner[0][j];
    }

    cout << endl;
    cout << "Teraz nastepuje losowa wymiana genow miedzy rodzicami i powinno powstac takie oto dziecko: " << endl;

    vector<vector<int>> child = generateChild(winner, parent);

    for(int j = 0; j < 8; j++){
        cout << child[0][j];
    }

    cout << endl;
    cout << "Ale bywa tak, ze geny mutuja, wiec dziecko posiada nastepujace geny: " << endl;

    child = geneticMutation(child);

    for(int j = 0; j < 8; j++){
        cout << child[0][j];
    }

    cout << endl;

    vector<int> childScore = fitness(child);

    cout << "To dziecko ma geny idealne w " << childScore[0] << "%" << endl;
    cout << "I oto bylo pierwsze pokolenie, teraz zobaczmy jak zmienia sie geny, jeszcze w 2, 3 i 1000" << endl << endl;

    parent = child;

    child.clear();
    candidates.clear();
    candidatesScores.clear();
    scoreParent.clear();
    choosen.clear();
    choosenCandidatesScores.clear();
    winner.clear();

    for(int i = 2; i < 1001; i++){
        candidates = candidatesForParent();

        if (i == 2 or i == 3 or i == 1000){
            cout << "Pokolenie " << i << " kandydaci: " << endl;
            for (auto & i : candidates) {
                for (int j = 0; j < i.size(); j++)
                    cout << i[j];
                cout << endl;
            }
        }

        candidatesScores = fitness(candidates);
        sumOfFitness = 0;

        if (i == 2 or i == 3 or i == 1000){
            cout << "Ich wyniki prezentuja sie nastepujaco: " << endl;
            for(auto c: candidatesScores){
                cout << c << "%" << endl;
            }
        }

        for (int fitnes: candidatesScores) {
            sumOfFitness += fitnes;
        }

        choosen = roulette(candidatesScores, sumOfFitness, candidates);
        choosenCandidatesScores = fitness(choosen);
        winner = tournament(candidatesScores, choosen);

        if (i == 2 or i == 3 or i == 1000){
            cout << "Wygrywa: " << endl;
            for(int j = 0; j < 8; j++){
                cout << winner[0][j];
            }
            cout << endl;
        }

        child = generateChild(winner, parent);

        if (i == 2 or i == 3 or i == 1000){
            cout << "Powstaje dziecko z genami: ";
            for(int j = 0; j < 8; j++){
                cout << child[0][j];
            }
            cout << endl;
        }

        child = geneticMutation(child);

        if (i == 2 or i == 3 or i == 1000){
            cout << "Ktore po mutacji jest nastepujace: ";
            for(int j = 0; j < 8; j++){
                cout << child[0][j];
            }
            cout << endl;
        }

        childScore = fitness(child);

        if (i == 2 or i == 3 or i == 1000){
            cout << "To dziecko ma geny idealne w " << childScore[0] << "%" << endl;
            cout << endl;
        }

        parent = child;

        child.clear();
        candidates.clear();
        candidatesScores.clear();
        scoreParent.clear();
        choosen.clear();
        choosenCandidatesScores.clear();
        winner.clear();
    }
}