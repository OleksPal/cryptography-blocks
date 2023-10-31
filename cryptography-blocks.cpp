#include <iostream>
#include <sstream>
#include <tuple>
#include <fstream>

using namespace std;

class PBlock {
private:
    int bits[8] = { 0,0,0,0,0,0,0,0 };
    int permutationOrder[8] = { 0,7,2,5,6,1,3,4 };

    int* copyBits() {
        static int copy[8];

        for (int i = 0; i < 8; i++)
            copy[i] = bits[i];

        return copy;
    }

    int* createRevesePermutationOrder() {
        static int revesePermutationOrder[8];

        for (int i = 0; i < 8; i++)
        {
            auto iter = find(permutationOrder, permutationOrder + 7, i);
            if (iter != permutationOrder + 8)
                revesePermutationOrder[i] = distance(permutationOrder, iter);
        }

        return revesePermutationOrder;
    }

public:
    void setBits(string input) {
        if (input.length() == 8) {
            for (int i = 0; i < 8; i++)
                bits[i] = input[i] - '0';
        }
    }
    
    string getBits() {
        string output = "";
        for (int i = 0; i < 8; i++)
            output += bits[i] + '0';

        return output;
    }

    void setPermutationOrder(string input) {
        if (input.length() == 8) {
            for (int i = 0; i < 8; i++)
                permutationOrder[i] = input[i] - '0';
        }
    }

    string getPermutationOrder() {
        string output = "";
        for (int i = 0; i < 8; i++)
            output += permutationOrder[i] + '0';

        return output;
    }

    void transform() {
        int* oldBits = copyBits();

        for (int i = 0; i < 8; i++)
            bits[i] = oldBits[permutationOrder[i]];
    }

    void reverseTransform() {
        int* revesePermutationOrder = createRevesePermutationOrder();
        int* oldBits = copyBits();

        for (int i = 0; i < 8; i++)
            bits[i] = oldBits[revesePermutationOrder[i]];
    }
};

class SBlock {
private:
    int bits[8] = { 0,0,0,0,0,0,0,0 };
    string** permutationTable = NULL;

    tuple<int, int> getPositionInTable() {
        int row = 0, col = 0;
        for (int i = 0; i < 4; i++) {
            row += bits[i] * pow(2, 3 - i);
            col += bits[i + 4] * pow(2, 3 - i);
        }

        return { row, col };
    }

    string coordinatesToHex(int row, int column) {
        stringstream ss;
        ss << hex << row << column;
        string res(ss.str());

        return res;
    } 

    int hexToInt(char value) {
        stringstream ss;
        ss << hex << value;
        int result;
        ss >> result;

        return result;
    }

    string** createPermutationTable(string path) {
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

    string** createReversePermutationTable() {
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
public:
    void setBits(string input) {
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

    string getBits() {
        string output = "";
        for (int i = 0; i < 8; i++)
            output += bits[i] + '0';

        return output;
    }

    void setPermutationTable(string path) {
        permutationTable = createPermutationTable(path);
    }

    string getPermutationTable() {
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

    void transform() {
        auto position = getPositionInTable();
        int row = get<0>(position);
        int column = get<1>(position);

        setBits(permutationTable[row][column]);
    }

    void reverseTransform() {
        string** reversePermutationTable = createReversePermutationTable();

        auto position = getPositionInTable();
        int row = get<0>(position);
        int column = get<1>(position);

        setBits(reversePermutationTable[row][column]);
    }
};

int main()
{
    PBlock pb;
    pb.setBits("10100110");
    cout << "P-Block original bits: " << pb.getBits() << endl;
    pb.setPermutationOrder("27016354");
    cout << "P-Block permutation order: " << pb.getPermutationOrder() << endl;
    pb.transform();
    cout << "P-Block transformed bits: " << pb.getBits() << endl;
    pb.reverseTransform();
    cout << "P-Block bits after reverse transformation: " << pb.getBits() << endl;

    SBlock sb;
    sb.setBits("11100111");
    cout << "S-Block original bits: " << sb.getBits() << endl;
    sb.setPermutationTable("Forward-S-box-table.txt");
    cout << "S-Block permutation table: \n" << sb.getPermutationTable() << endl;
    sb.transform();
    cout << "S-Block transformed bits: " << sb.getBits() << endl;
    sb.reverseTransform();
    cout << "S-Block bits after reverse transformation: " << sb.getBits() << endl;
}
