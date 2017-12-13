#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../RC4/RC4.h"

using namespace std;

int main(){
	srand(time(NULL));
	vector<int> k;
	for(int i = 0; i < 256; i++){
		k.push_back(rand() % 256);
	}
	vector<int> key = RC4::getRC4Key(1024, 100, k);
	
	RC4::deleteRepeat(key, 1024);
	for(int i = 0; i < key.size(); i++){
		cout<<i<<"->"<<key[i]<<endl;
	}
}
