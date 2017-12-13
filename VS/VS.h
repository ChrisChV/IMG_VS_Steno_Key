#ifndef VS_H
#define VS_H

#include <iostream>
#include <tuple>
#include <vector>
#include "../CImg.h"
#include "../Utils/sad.h"

using namespace std;
using namespace cimg_library;

tuple<CImg<int>,CImg<int>> binaryVSdiv(CImg<int> &secretImg, CImg<int> &img);
CImg<int> binaryVSmatch(CImg<int> &share1, CImg<int> &share2);
CImg<int> generateShare(CImg<int> &img);
CImg<int> generateImageKey(vector<int> key, int height, int width);
vector<int> generateStegoKey(CImg<int> imageKey);


#endif







