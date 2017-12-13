#include <iostream>
#include "../Steno/Steno.h"
#include "../VS/VS.h"

using namespace std;

int main(){
	CImg<int> img1("milla2.bmp");
	CImg<int> img2("milla2.bmp");
	vector<int> stegoKey = hideMsg("hola mundo", img2);
	CImg<int> imageKey = generateImageKey(stegoKey, img1.height(), img1.width());
	stegoKey = generateStegoKey(imageKey);
	string msg = revealMsg(img2, stegoKey);
	cout<<msg<<endl;
	(img1,img2,imageKey).display();
}
