#ifndef STENO_H
#define STENO_H

#include <iostream>
#include <pthread.h>
#include "../Utils/sad.h"
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

void * threadHideShare(void * arg);
void hideShare(CImg<int> &img, CImg<int> &share);
void * threadGetShare(void * arg);
CImg<int> getShare(CImg<int> &img);

#endif