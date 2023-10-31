#include <iostream>
#include "PBlock.h"
#include "SBlock.h"

using namespace std;

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
    cout << "P-Block bits after reverse transformation: " << pb.getBits() << endl << endl;

    SBlock sb;
    sb.setBits("11100111");
    cout << "S-Block original bits: " << sb.getBits() << endl;
    sb.setPermutationTable("Forward-S-box-table.txt");
    cout << "S-Block permutation table: \n" << sb.getPermutationTable();
    sb.transform();
    cout << "S-Block transformed bits: " << sb.getBits() << endl;
    sb.reverseTransform();
    cout << "S-Block bits after reverse transformation: " << sb.getBits() << endl;
}