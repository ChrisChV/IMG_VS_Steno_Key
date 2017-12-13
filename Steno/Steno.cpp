#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Steno.h"
#include "../Utils/Utils.h"
#include "../RC4/RC4.h"

using namespace std;
using namespace cimg_library;

void * threadHideShare(void * arg){
	ThreadArg tArg = *((ThreadArg *) arg);
	int ini = tArg.ini;
	int end = tArg.end;
	CImg<int> * share = tArg.arg;
	CImg<int> * img = tArg.res;
	string byte = "";
	for(int i = ini; i < end; i++){
		for(int j = 0; j < img->width(); j++){
			byte = toBinary((*img)(j,i,0,2));
			if((*share)(j,i,0,0) == 1) byte[BITS_PER_PIXEL - 1] = '1';
			else byte[BITS_PER_PIXEL - 1] = '0';
			(*img)(j,i,0,2) = sToDecimal(byte);
		}
	}
}

void hideShare(CImg<int> &img, CImg<int> &share){
	pthread_t threads[NUM_THREADS];
	ThreadArg args[NUM_THREADS];
	int despl = share.height() / NUM_THREADS;
	for(int i = 0; i < NUM_THREADS; i++){
		args[i].ini = i * despl;
		if(i == NUM_THREADS - 1) args[i].end = share.height();
		else args[i].end = args[i].ini + despl;
		args[i].arg = &share;
		args[i].res = &img;
		pthread_create(&threads[i], NULL, threadHideShare, (void *) &args[i]);
	}
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
}

void * threadGetShare(void * arg){
	ThreadArg tArg = *((ThreadArg *) arg);
	int ini = tArg.ini;
	int end = tArg.end;
	CImg<int> * share = tArg.res;
	CImg<int> * img = tArg.arg;
	string byte = "";
	for(int i = ini; i < end; i++){
		for(int j = 0; j < share->width(); j++){
			byte = toBinary((*img)(j,i,0,2));
			if(byte[BITS_PER_PIXEL - 1] == '1') (*share)(j,i,0,0) = 1;
			else (*share)(j,i,0,0) = 0;
		}
	}
}


CImg<int> getShare(CImg<int> &img){
	CImg<int> share(img.width(), img.height(), 1, 1);
	pthread_t threads[NUM_THREADS];
	ThreadArg args[NUM_THREADS];
	int despl = share.height() / NUM_THREADS;
	for(int i = 0; i < NUM_THREADS; i++){
		args[i].ini = i * despl;
		if(i == NUM_THREADS - 1) args[i].end = share.height();
		else args[i].end = args[i].ini + despl;
		args[i].arg = &img;
		args[i].res = &share;
		pthread_create(&threads[i], NULL, threadGetShare, (void *) &args[i]);
	}
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	return share;
}

vector<string> divideMsg(string msg){
	vector<string> res;
	int num = 0;
	string byte = "";
	string bloque = "";
	for(char c : msg){
		num = (int) c;
		byte = toBinary(num);
		for(int i = 0; i < BITS_PER_PIXEL; i+=2){
			bloque.clear();
			bloque.push_back(byte[i]);
			bloque.push_back(byte[i + 1]);
			res.push_back(bloque);
		}
	}
	return res;
}

vector<int> hideMsg(string msg, CImg<int> &img){
	srand(time(NULL));
	vector<int> k;
	for(int i = 0; i < TAM_KEY; i++){
		k.push_back(rand() % TAM_KEY);
	}
	string byte = "";
	int fil = 0;
	int col = 0;
	int sizeImage = img.width() * img.height();
	vector<string> msgBinBlocks = divideMsg(msg);
	vector<int> stegoKey = RC4::getRC4Key(sizeImage, msgBinBlocks.size(), k);
	RC4::deleteRepeat(stegoKey, sizeImage);
	sort(stegoKey.begin(), stegoKey.end());
	for(int i : stegoKey){
		cout<<i<<endl;
	}
	for(int i = 0; i < stegoKey.size(); i++){
		int pos = stegoKey[i];
		fil = pos / img.width();
		col = pos % img.width();
		byte = toBinary(img(col, fil, 0, 0));
		byte[BITS_PER_PIXEL - 2] = msgBinBlocks[i][0];
		byte[BITS_PER_PIXEL - 1] = msgBinBlocks[i][1];
		img(col, fil, 0, 0) = sToDecimal(byte);
	}
	return stegoKey;
}

string linkMsg(vector<string> msgBinBlocks){
	string msg = "";
	string byte = "";
	for(int i = 0; i < msgBinBlocks.size(); i+=4){
		byte = msgBinBlocks[i];
		byte = byte + msgBinBlocks[i + 1];
		byte = byte + msgBinBlocks[i + 2];
		byte = byte + msgBinBlocks[i + 3];
		msg.push_back((char) sToDecimal(byte));
	}
	return msg;
}

string revealMsg(CImg<int> &img, vector<int> stegoKey){
	int fil = 0;
	int col = 0;
	string byte = "";
	string msgBlock = "";
	vector<string> msgBinBlocks;
	for(int pos : stegoKey){
		fil = pos / img.width();
		col = pos % img.width();
		msgBlock.clear();
		byte = toBinary(img(col, fil, 0, 0));
		msgBlock.push_back(byte[BITS_PER_PIXEL - 2]);
		msgBlock.push_back(byte[BITS_PER_PIXEL - 1]);
		msgBinBlocks.push_back(msgBlock);
	}
	return linkMsg(msgBinBlocks);
}