# cryptography-blocks

## Description
Program implementation of S-block and P-block algorithms with 8 bits input and output data size (forward and reverse transformation).

## Usage of P-block
```cpp
// Creating P-Block object
PBlock pb;

// Setting start set of bits
pb.setBits("10100110");

// Setting permutation order for P-block starting with 0
pb.setPermutationOrder("27016354");

// Transforming start set of bits by using permutation order
pb.transform();

// Getting and printing result of transforming
cout << "P-Block transformed bits: " << pb.getBits() << endl;

// Reverse transforming of bits by using permutation order
pb.reverseTransform();

// Getting and printing result of reverse transforming
cout << "P-Block bits after reverse transformation: " << pb.getBits() << endl;
```

## Usage of S-block
```cpp
// Creating S-Block object
SBlock sb;

// Setting start set of bits
sb.setBits("11100111");

// Setting permutation table for S-block from text file
sb.setPermutationTable("Forward-S-box-table.txt");

// Printing permutation table of S-Block
cout << "S-Block permutation table: \n" << sb.getPermutationTable();

// Transforming start set of bits by using permutation table
sb.transform();

// Getting and printing result of transforming
cout << "S-Block transformed bits: " << sb.getBits() << endl;

// Reverse transforming of bits by using permutation table
sb.reverseTransform();

// Getting and printing result of reverse transforming
cout << "S-Block bits after reverse transformation: " << sb.getBits() << endl;