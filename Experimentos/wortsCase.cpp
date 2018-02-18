#include <iostream>

using namespace std;

int main(int argc, char ** argv){
	if(argc != 4){
		cout<<"Faltan argumentos <img> <msg> <lsb>"<<endl;
		return 0;
	}
	string img = argv[1];
	string msg = argv[2];
	string lsb = argv[3];
	string comm = "./run -h imgs/" + img + ".bmp peor_lsb_" + lsb + " " + msg;
	system(comm.c_str());
	string comm2 = "./run -p imgs/" + img + ".bmp  imgs/" + img + ".cover.bmp";
	system(comm2.c_str());
}