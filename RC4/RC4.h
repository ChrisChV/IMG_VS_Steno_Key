#ifndef RC4_H
#define RC4_H

#include <iostream>
#include <vector>
#include <map>
#include "RC4.h"

using namespace  std;

namespace RC4{

	vector<int> KSA(int sizeImage, vector<int> key){
		vector<int> vectS(sizeImage);
		vector<int> vectT(sizeImage);
		int actualIforKey = 0;
		for(int i = 0; i < sizeImage; i++){
			vectS[i] = i;
			vectT[i] = (int) (key[actualIforKey]) % sizeImage;
			actualIforKey++;
			if(actualIforKey == key.size()) actualIforKey = 0;
		}
		int j = 0;
		for(int i = 0; i < sizeImage; i++){
			j =  (j + vectS[i] + vectT[i]) % sizeImage;
			swap(vectS[i], vectS[j]);
		}
		return vectS;
	}

	vector<int> PRGA(int sizeMsg, vector<int> vectS){
		vector<int> key(sizeMsg);
		int i = 0;
		int j = 0;
		int t = 0;
		int sizeImage = vectS.size();
		for(int k = 0; k < sizeMsg; k++){
			i = (i + 1) % sizeImage;
			j = (j + vectS[i]) % sizeImage;
			swap(vectS[i], vectS[j]);
			t = (vectS[i] + vectS[j]) % sizeImage;
			key[k] = vectS[t];
		}
		return key;
	}

	vector<int> getRC4Key(int sizeImage, int sizeMsg, vector<int> key){
		return PRGA(sizeMsg, KSA(sizeImage, key));
	}

	void deleteRepeat(vector<int> &key, int sizeImage){
		vector<bool> nums(sizeImage, false);
		vector<int> repetidos;
		int actualFalse = -1;
		for(int i = 0; i < key.size(); i++){
			if(nums[key[i]] == false) nums[key[i]] = true;
			else repetidos.push_back(i);
		}
		while(true){
			actualFalse++;
			if(actualFalse == nums.size()) throw("Ya se utilizaron todos los numeros, no se puede eliminar repetidos");
			if(nums[actualFalse] == false) break;
		}
		if(repetidos.empty()) cout<<"No hay repetidos"<<endl;
		for(int i : repetidos){
			key[i] = actualFalse;
			nums[actualFalse] = true;
			while(true){
				actualFalse++;
				if(actualFalse == nums.size()) throw("Ya se utilizaron todos los numeros, no se puede eliminar repetidos");
				if(nums[actualFalse] == false) break;
			}
		}
	}
}

#endif