#include <iostream>
#include "../VS/VS.h"

using namespace std;

int main(){
	CImg<int> img1("milla2.bmp");
	CImg<int> share = generateShare(img1);
	CImg<int> share2;
	CImg<int> temp;
	CImg<int> img2(img1.width(),img1.height(),1,1);
	img2.rand(0,1);
	tie(temp, share2) = binaryVSdiv(img2, img1);
	temp = binaryVSmatch(img1, share2);
	(img1,img2,temp).display();
}