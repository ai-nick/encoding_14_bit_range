#include <iostream>
#include <fstream>
using namespace std;


int writeFile () 
{
  ofstream myfile;
  myfile.open ("test.txt");
  for(int i = -5; i < 6; i++){
    myfile << i << "\n";      
  }
  myfile.close();
  return 0;
}

int main() {
    cout<<"creating test file hold your horses!"<<endl;
    return writeFile();
}