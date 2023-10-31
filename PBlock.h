#pragma once

#include <iostream>

using namespace std;

class PBlock {
private:
    int bits[8] = { 0,0,0,0,0,0,0,0 };
    int permutationOrder[8] = { 0,7,2,5,6,1,3,4 };

    int* copyBits();

    int* createRevesePermutationOrder();

public:
    void setBits(string input);
    string getBits();

    void setPermutationOrder(string input);
    string getPermutationOrder();

    void transform();
    void reverseTransform();
};