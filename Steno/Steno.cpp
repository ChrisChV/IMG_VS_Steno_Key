#include <iostream>
#include "Steno.h"
#include "../Utils/Utils.h"

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

/*
void hideShare(CImg<int> &img, CImg<int> &share){
	string byte = "";
	for(int i = 0; i < share.height(); i++){
		for(int j = 0; j < share.width(); j++){
			int num = img(j,i,0,2);
			byte = toBinary(num);
			byte[BITS_PER_PIXEL - 1] = share(j,i,0,0);
			img(j,i,0,2) = sToDecimal(byte);
		}
	}
}
*/
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

