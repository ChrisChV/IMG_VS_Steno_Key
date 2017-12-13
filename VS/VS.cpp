#include <iostream>
#include <pthread.h>
#include "VS.h"
#include "../Utils/Utils.h"

using namespace cimg_library;
using namespace std;


tuple<CImg<int>,CImg<int>> binaryVSdiv(CImg<int> &secretImg, CImg<int> &img){
	CImg<int> share1 = generateShare(img);
	CImg<int> share2 = share1 ^ secretImg;
	return make_tuple(share1,share2);
}

CImg<int> binaryVSmatch(CImg<int> &img, CImg<int> &share2){
	CImg<int> share1 = generateShare(img);
	return share1 ^ share2;
}


void * threadGenerateShare(void * arg){
	ThreadArg tArg = *((ThreadArg *)arg);
	int ini = tArg.ini;
	int end = tArg.end;
	CImg<int> * G_channel = tArg.arg;
	CImg<int> * share = tArg.res;
	string byte = "";
	for(int i = ini; i < end; i++){
		for(int j = 0; j < share->width(); j++){
			byte = toBinary((*G_channel)(j,i,0,0));
			if(byte[BIT_SHARE] == '1') (*share)(j,i,0,0) = 1;
			else (*share)(j,i,0,0) = 0;
		}
	}
}

CImg<int> generateShare(CImg<int> &img){
	CImg<int> G_channel = img.get_channel(1);
	CImg<int> share(G_channel.width(),G_channel.height(),1,1);
	int despl = G_channel.height() / NUM_THREADS;
	pthread_t threads[NUM_THREADS];
	ThreadArg args[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++){
		args[i].ini = i * despl;
		if(i == NUM_THREADS - 1) args[i].end = share.height();
		else args[i].end = args[i].ini + despl;
		args[i].arg = &G_channel;
		args[i].res = &share;
		pthread_create(&threads[i], NULL, threadGenerateShare, (void *) &args[i]);
	}
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}
	return share;
}

