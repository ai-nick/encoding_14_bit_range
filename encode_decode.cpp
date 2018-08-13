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
    short int num = shmumber << 1; // copy our number with bits shifted to put our second 7 bit set in the second byte
    for (int ix = 16; ix > 8; ix--){
        int x = (num >> ix) & 1U; //this could be done in place like you see in the decoding function
        shmumber ^= (-x ^ shmumber) & (1UL << ix); 
    }
    shmumber &= ~(1UL << 7);
    bitset<16> n(shmumber);
    stringstream hxstring;
    hxstring <<  hex << n.to_ulong();
    return hxstring.str();
}

short int decode(string snum){
    // we will simply reverse the operations of the encoding process
    stringstream ss(snum);
    short int bnum;
    ss >> hex >> bnum;
    for(int ix = 7; ix < 15; ix++){
        int x = (bnum >> ix + 1) & 1UL;
        bnum ^= (-x ^ bnum) & (1UL << ix);
    }
    return bnum - 8192;
}

int collect_input(){
    //calls itself recursively untill user enters q
    char e_or_d;
    string tempString;
    cout<<"Enter \"e\" to encode or \"d\" to decode or \"q\" to quit"<<endl;
    cin>>e_or_d;
    e_or_d = tolower(e_or_d);
    switch(e_or_d){
        case 'e':
            short int tempNum;
            cout << "please enter a number in the range (-8192, 8191) to be encoded."<<endl;
            cin>>tempNum;
            cout << "the encoded value is: ";
            cout << encode(tempNum) << endl;
            collect_input();
            break;
        case 'd' :
            cout << "please enter a 4 character hexadecimal in the range (0x00,0x7f) to be decoded."<<endl;
            cin>> tempString;
            cout << "the decoded value is: ";
            cout << decode(tempString)<< endl;
            collect_input();
            break;
        case 'q':
            return 0;
            break;
        default:
            cout << "invalid value entered please try again!"<<endl;
            collect_input();
            break;
    }
}


int main(){
    return collect_input();
}

