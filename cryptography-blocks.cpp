#include <iostream>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;

class PBlock {
private:
    unsigned char bytes[8] = { 0,0,0,0,0,0,0,0 };
    unsigned char encryption_mask[8] = { 0,7,2,5,6,1,3,4 };

    unsigned char* copyBytes() {
        static unsigned char copy[8];

        for (int i = 0; i < 8; i++)
            copy[i] = bytes[i];

        return copy;
    }

    unsigned char* createDecryptionMask() {
        static unsigned char decryption_mask[8];

        for (int i = 0; i < 8; i++)
        {
            auto iter = find(encryption_mask, encryption_mask + 7, i);
            if (iter != encryption_mask + 8)
                decryption_mask[i] = distance(encryption_mask, iter);
        }

        return decryption_mask;
    }

public:
    void setBytes(string input) {
        if (input.length() == 8) {
            for (int i = 0; i < 8; i++)
                bytes[i] = input[i];
        }
    }
    
    string getBytes() {
        string output = "";
        for (int i = 0; i < 8; i++)
            output += bytes[i];

        return output;
    }

    void encrypt() {
        unsigned char* old_bytes = copyBytes();

        for (int i = 0; i < 8; i++)
            bytes[i] = old_bytes[encryption_mask[i]];
    }

    void decrypt() {
        unsigned char* decryption_mask = createDecryptionMask();
        unsigned char* old_bytes = copyBytes();

        for (int i = 0; i < 8; i++)
            bytes[i] = old_bytes[decryption_mask[i]];
    }
};

class SBlock {
private:
    int bytes[8] = { 0,0,0,0,0,0,0,0 };
    string encryption_mask[16][16] =
    {
        {"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
        {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"}
    };
    string decryption_mask[16][16] =
    {
        {"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},
        {"4"},
    };

    tuple<int, int> getPositionInTable() {
        int row = 0, col = 0;
        for (int i = 0; i < 4; i++) {
            row += bytes[i] * pow(2, 3 - i);
            col += bytes[i + 4] * pow(2, 3 - i);
        }

        return { row, col };
    }
public:
    void setBytes(string input) {
        if (input.length() == 2) { // set through hex value
            stringstream ss;
            ss << hex << input;

            unsigned int n;
            while (ss >> n) {
                for (int i = 0; i < 8; i++)
                    bytes[7 - i] = ((n >> i) & 1) ? 1 : 0;
            }
        }

        if (input.length() == 8) { // set through binary value
            for (int i = 0; i < 8; i++)
                bytes[i] = input[i] - '0';
        }        
    }

    string getBytes() {
        string output = "";
        for (int i = 0; i < 8; i++)
            output += bytes[i] + '0';

        return output;
    }

    void encrypt() {
        auto position = getPositionInTable();
        int row = get<0>(position);
        int column = get<1>(position);

        setBytes(encryption_mask[row][column]);
    }

    void decrypt() {
        auto position = getPositionInTable();
        int row = get<0>(position);
        int column = get<1>(position);

        setBytes(decryption_mask[row][column]);
    }
};

int main()
{
    /*PBlock p;
    p.setBytes("01100110");
    cout << p.getBytes() << endl;
    p.encrypt();
    cout << p.getBytes() << endl;
    p.decrypt();
    cout << p.getBytes();*/

    SBlock sb;
    sb.setBytes("00001001");
    cout << sb.getBytes() << endl;
    sb.encrypt();
    cout << sb.getBytes() << endl;
    sb.decrypt();
    cout << sb.getBytes() << endl;
}
