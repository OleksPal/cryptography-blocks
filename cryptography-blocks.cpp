#include <iostream>
#include <algorithm>

using namespace std;

class PBlock {
private:
    unsigned char bytes[8] = { 0,0,0,0,0,0,0,0 };
    unsigned char encryption_mask[8] = { 4,7,1,5,0,2,3,6 };

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

int main()
{
    PBlock p;
    p.setBytes("01100110");
    cout << p.getBytes() << endl;
    p.encrypt();
    cout << p.getBytes() << endl;
    p.decrypt();
    cout << p.getBytes();
}
