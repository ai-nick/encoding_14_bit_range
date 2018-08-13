#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <bitset> // memcpy
using namespace std;

string encode(short int shmumber){
    if (shmumber < -8192 or shmumber > 8191){
        return "number out of range for this encoder";
    } else {
        shmumber = shmumber + 8192;
    }
    short int num = shmumber << 1;
    for (int ix = 16; ix > 8; ix--){
        int x = (num >> ix) & 1U;
        shmumber ^= (-x ^ shmumber) & (1UL << ix);
    }
    shmumber &= ~(1UL << 7);
    bitset<16> n(shmumber);
    cout << "after: " << n << endl;
    stringstream hxstring;
    hxstring <<  hex << n.to_ulong();
    cout << hxstring.str() <<endl;
    return hxstring.str();
}

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

int collect_input(){
    char e_or_d;
    cout<<"Enter \"e\" to encode or \"d\" to decode or \"q\" to quit"<<endl;
    cin>>e_or_d;
    e_or_d = tolower(e_or_d);
    switch(e_or_d){
        case "e":
            short int tempNum;
            cout << "please enter a number in the range (-8192, 8191) to be encoded."<<endl;
            cin>>tempNum;
            cout << "the encoded value is: ";
            cout << encode(tempNum) << endl;
            break;
        case "d" :
            short int tempNum;
            cout << "please enter a 4 character hexadecimal in the range (0x00,0x7f) to be decoded."<<endl;
            cin>>tempNum;
            cout << "the decoded value is: ";
            break;
        case "q":
            return 0;
        default:
            cout << "invalid value entered please try again!"<<endl;
            collect_input();
    }
}


int main(){
    return collect_input();
}

