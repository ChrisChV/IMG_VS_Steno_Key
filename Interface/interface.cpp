#include <iostream>
#include "interface.h"
#include "../Utils/Utils.h"

using namespace std;

string hide(string msgPath, string imagePath){
	string msg = getMsgFromFile(msgPath);
	cout<<"Mensaje a ocultar:"<<endl<<msg<<endl;
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	CImg<int> share1;
	CImg<int> share2;
	vector<int> stegoKey = hideMsg(msg, image);
	CImg<int> imageKey = generateImageKey(stegoKey, image.height(), image.width());
	tie(share1, share2) = binaryVSdiv(imageKey, image);
	hideShare(image, share2);
	string newImagePath = addStringToFile(imagePath, "_cover");
	image.save(newImagePath.c_str());
	return newImagePath;
}

string reveal(string imagePath){
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	CImg<int> share2 = getShare(image);
	CImg<int> imageKey = binaryVSmatch(image, share2);
	vector<int> stegoKey = generateStegoKey(imageKey);
	return revealMsg(image, stegoKey);
}

double getPSRN(string imagePath1, string imagePath2){
	imagePath1 = convertToBMP(imagePath1);
	imagePath2 = convertToBMP(imagePath2);
	CImg<int> image1(imagePath1.c_str());
	CImg<int> image2(imagePath2.c_str());
	return image1.PSNR(image2);
}