#include "PBlock.h"

int* PBlock::copyBits() {
    static int copy[8];

    for (int i = 0; i < 8; i++)
        copy[i] = bits[i];

    return copy;
}

int* PBlock::createRevesePermutationOrder() {
    static int revesePermutationOrder[8];

    for (int i = 0; i < 8; i++)
    {
        auto iter = find(permutationOrder, permutationOrder + 7, i);
        if (iter != permutationOrder + 8)
            revesePermutationOrder[i] = distance(permutationOrder, iter);
    }

    return revesePermutationOrder;
}

void PBlock::setBits(string input) {
    if (input.length() == 8) {
        for (int i = 0; i < 8; i++)
            bits[i] = input[i] - '0';
    }
}

string PBlock::getBits() {
    string output = "";
    for (int i = 0; i < 8; i++)
        output += bits[i] + '0';

    return output;
}

void PBlock::setPermutationOrder(string input) {
    if (input.length() == 8) {
        for (int i = 0; i < 8; i++)
            permutationOrder[i] = input[i] - '0';
    }
}

string PBlock::getPermutationOrder() {
    string output = "";
    for (int i = 0; i < 8; i++)
        output += permutationOrder[i] + '0';

    return output;
}

void PBlock::transform() {
    int* oldBits = copyBits();

    for (int i = 0; i < 8; i++)
        bits[i] = oldBits[permutationOrder[i]];
}

void PBlock::reverseTransform() {
    int* revesePermutationOrder = createRevesePermutationOrder();
    int* oldBits = copyBits();

    for (int i = 0; i < 8; i++)
        bits[i] = oldBits[revesePermutationOrder[i]];
}