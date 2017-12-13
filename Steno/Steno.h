#ifndef STENO_H
#define STENO_H

#include <iostream>
#include <pthread.h>
#include <vector>
#include "../Utils/sad.h"
#include "../CImg.h"

using namespace std;
using namespace cimg_library;

void hideShare(CImg<int> &img, CImg<int> &share);
CImg<int> getShare(CImg<int> &img);
vector<int> hideMsg(string msg, CImg<int> &img);
string revealMsg(CImg<int> &img, vector<int> stegoKey);

#endif