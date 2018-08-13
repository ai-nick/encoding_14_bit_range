#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <bitset> // memcpy
using namespace std;

short int decode(string snum){
    stringstream ss(snum);
    short int bnum;
    ss >> hex >> bnum;
    for(int ix = 7; ix < 15; ix++){
        int x = (bnum >> ix + 1) & 1UL;
        bnum ^= (-x ^ bnum) & (1UL << ix);
    }
    cout << bnum << endl;
    return bnum - 8192;
}



int main(){
    string temp14;
    ifstream tests;
    tests.open("test_encoded.txt");
    ofstream myfile;
    myfile.open ("test_decoded.txt");
    while(tests >> temp14){
        //cout << temp14 << endl;
        myfile << decode(temp14) <<"\n";
    }
    myfile.close();
    tests.close();
    return 0;
}