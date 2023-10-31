#pragma once

#include <iostream>

using namespace std;

class SBlock {
private:
    int bits[8] = { 0,0,0,0,0,0,0,0 };
    string** permutationTable = NULL;

    tuple<int, int> getPositionInTable();

    string coordinatesToHex(int row, int column);

    int hexToInt(char value);

    string** createPermutationTable(string path);
    string** createReversePermutationTable();

public:
    void setBits(string input);
    string getBits();

    void setPermutationTable(string path);
    string getPermutationTable();

    void transform();
    void reverseTransform();
};