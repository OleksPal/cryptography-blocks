#include <sstream>
#include <tuple>
#include <fstream>
#include "SBlock.h"

tuple<int, int> SBlock::getPositionInTable() {
    int row = 0, col = 0;
    for (int i = 0; i < 4; i++) {
        row += bits[i] * pow(2, 3 - i);
        col += bits[i + 4] * pow(2, 3 - i);
    }

    return { row, col };
}

string SBlock::coordinatesToHex(int row, int column) {
    stringstream ss;
    ss << hex << row << column;
    string res(ss.str());

    return res;
}

int SBlock::hexToInt(char value) {
    stringstream ss;
    ss << hex << value;
    int result;
    ss >> result;

    return result;
}

string** SBlock::createPermutationTable(string path) {
    string** permutationTable = new string * [16];
    ifstream iFile;
    iFile.open(path);

    for (int i = 0; i < 16; i++) {
        permutationTable[i] = new string[16];
        for (int j = 0; j < 16; j++) {
            iFile >> permutationTable[i][j];
        }
    }

    iFile.close();

    return permutationTable;
}

string** SBlock::createReversePermutationTable() {
    string** reversePermutationTable = new string * [16];

    for (int i = 0; i < 16; i++) { // initialization of 2d array
        reversePermutationTable[i] = new string[16];
    }

    for (int i = 0; i < 16; i++) {
        reversePermutationTable[i] = new string[16];
        for (int j = 0; j < 16; j++) {
            int row = hexToInt(permutationTable[i][j][0]);
            int column = hexToInt(permutationTable[i][j][1]);
            reversePermutationTable[row][column] = coordinatesToHex(i, j);
        }
    }

    return reversePermutationTable;
}

void SBlock::setBits(string input) {
    if (input.length() == 3 && input[2] == ' ') // remove excessive space
        input.pop_back();

    if (input.length() == 2) { // set through hex value
        stringstream ss;
        ss << hex << input;

        unsigned int n;
        while (ss >> n) {
            for (int i = 0; i < 8; i++)
                bits[7 - i] = ((n >> i) & 1) ? 1 : 0;
        }
    }
    else if (input.length() == 8) { // set through binary value
        for (int i = 0; i < 8; i++)
            bits[i] = input[i] - '0';
    }
}

string SBlock::getBits() {
    string output = "";
    for (int i = 0; i < 8; i++)
        output += bits[i] + '0';

    return output;
}

void SBlock::setPermutationTable(string path) {
    permutationTable = createPermutationTable(path);
}

string SBlock::getPermutationTable() {
    string output = "";
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++) {
            output += permutationTable[i][j] += " ";
        }
        output += "\n";
    }

    return output;
}

void SBlock::transform() {
    auto position = getPositionInTable();
    int row = get<0>(position);
    int column = get<1>(position);

    setBits(permutationTable[row][column]);
}

void SBlock::reverseTransform() {
    string** reversePermutationTable = createReversePermutationTable();

    auto position = getPositionInTable();
    int row = get<0>(position);
    int column = get<1>(position);

    setBits(reversePermutationTable[row][column]);
}