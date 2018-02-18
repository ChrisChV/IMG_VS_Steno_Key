#include <iostream>
#include "interface.h"
#include "../Utils/Utils.h"

using namespace std;

string hide(string msgPath, string imagePath, int tamLSB){
	string msg = getMsgFromFile(msgPath);
	//cout<<"Mensaje a ocultar:"<<endl<<msg<<endl;
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	CImg<int> share1;
	CImg<int> share2;
	vector<int> stegoKey = hideMsg(msg, image, tamLSB);
	CImg<int> imageKey = generateImageKey(stegoKey, image.height(), image.width());
	tie(share1, share2) = binaryVSdiv(imageKey, image);
	hideShare(image, share2);
	string newImagePath = addStringToFile(imagePath, ".cover");
	image.save(newImagePath.c_str());
	return newImagePath;
}

string reveal(string imagePath, int tamLSB){
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	CImg<int> share2 = getShare(image);
	CImg<int> imageKey = binaryVSmatch(image, share2);
	vector<int> stegoKey = generateStegoKey(imageKey);
	return revealMsg(image, stegoKey, tamLSB);
}

double getPSRN(string imagePath1, string imagePath2){
	imagePath1 = convertToBMP(imagePath1);
	imagePath2 = convertToBMP(imagePath2);
	CImg<int> image1(imagePath1.c_str());
	CImg<int> image2(imagePath2.c_str());
	return image1.PSNR(image2);
}

double getCapacity(string imagePath, int tamLSB){
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	double numberPixels = image.width() * image.height();
	CImg<int> share2 = getShare(image);
	CImg<int> imageKey = binaryVSmatch(image, share2);
	vector<int> stegoKey = generateStegoKey(imageKey);
	double numberEmbeddedBits = stegoKey.size() * tamLSB;
	return numberEmbeddedBits / numberPixels;
}

void display(string imagePath1, string imagePath2){
	CImg<int> image1(imagePath1.c_str());
	CImg<int> image2(imagePath2.c_str());
	(image1,image2).display();
}

void displayStegoKey(string imagePath){
	imagePath = convertToBMP(imagePath);
	CImg<int> image(imagePath.c_str());
	CImg<int> share2 = getShare(image);
	CImg<int> imageKey = binaryVSmatch(image, share2);
	imageKey.display();
}

