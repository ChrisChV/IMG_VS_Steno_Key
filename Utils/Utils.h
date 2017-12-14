#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cmath>
#include <tuple>
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

tuple<string,string> getExtension(string file);
string convertToBMP(string file);
string toBinary(int num);
int sToDecimal(string num);
string addStringToFile(string file, string add);
string getMsgFromFile(string msgPath);

struct ThreadArg{
	int ini;
	int end;
	CImg<int> *arg;
	CImg<int> *res;
	ThreadArg(){}
	ThreadArg(int ini, int end, CImg<int> * arg, CImg<int> * res){
		this->ini = ini;
		this->end = end;
		this->arg = arg;
		this->res = res;
	}
};

#endif