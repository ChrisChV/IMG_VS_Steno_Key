#include <iostream>
#include "../Steno/Steno.h"

using namespace std;

int main(){
	CImg<int> img1("milla2.bmp");
	CImg<int> share(img1.width(), img1.height(), 1, 1);
	share.rand(0,1);
	hideShare(img1, share);
	CImg<int> img2 = img1;
	CImg<int> res = getShare(img1);
	(img1, share, img2, res).display();
}
