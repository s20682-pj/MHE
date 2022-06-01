#include <vector>


using namespace std;
int howManyBin(vector<int> data, int binSize, int quantity){
    int numOfBins = 1;
    int sumInBin = 0;
    for (int i = 0; i < quantity; ++i) {
        int x = data.at(i);
        if (sumInBin + x <= binSize){
            sumInBin += data.at(i);
        } else{
            sumInBin = data.at(i);
            numOfBins++;
        }
    }
    return numOfBins;
}