#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cmath>
#include <tuple>
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

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

tuple<string,string> getExtension(string file){
	string pre = "";
	string post = "";
	bool flag = 0;
	for(char c : file){
		if(c == '.') flag = 1;
		else if(flag == 0) pre.push_back(c);
		else post.push_back(c);
	}
	return make_tuple(pre,post);
}

string convertToBMP(string file){
	string pre;
	string post;
	string command = "";
	tie(pre,post) = getExtension(file);
	if(post != "bmp"){
		command = "convert " + file + " " + pre + ".bmp";
		system(command.c_str());
		return pre + ".bmp";
	}
	return file;
}


string toBinary(int num){
	string res = "";
	int temp = 0;
	for(int i = 0; i < 8; i++){
		temp = pow(2,7 - i);
		if(num >= temp){
			num -= temp;
			res.push_back('1');
		}
		else res.push_back('0');
	}
	return res;
}

int sToDecimal(string num){
	int res = 0;
	for(int i = 0; i < num.size(); i++){
		if(num[i] == '1') res += pow(2,num.size() - 1 - i);
	}
	return res;
}

#endif