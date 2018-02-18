#include <iostream>
#include "../Interface/interface.h"

using namespace std;

int main(int argc, char ** argv){
	try{
		if(argc < 2) throw("Falta una opcion, utilice help para mas info");
		string option = argv[1];
		if(option == "help"){
			string comm = "cat help";
			system(comm.c_str());
		}
		else if(option == "-h"){
			if(argc != 5) throw("Faltan argumentos para -h, utilice help para mas info");
			string imagePath = argv[2];
			string msgPath = argv[3];
			string tamLSB = argv[4];
			string newImagePath = hide(msgPath, imagePath, stoi(tamLSB));
			cout<<"El mensaje ha sido guardado en "<<newImagePath<<endl;
		}
		else if(option == "-r"){
			if(argc != 4) throw("Faltan argumentos para -r, utilice help para mas info");
			string imagePath = argv[2];
			string tamLSB = argv[3];
			string msg = reveal(imagePath, stoi(tamLSB));
			cout<<"El mensaje secreto es:"<<endl<<msg<<endl;
		}
		else if(option == "-p"){
			if(argc != 4) throw("Faltan argumentos para -h, utilice help para mas info");
			string imagePath1 = argv[2];
			string imagePath2 = argv[3];
			double psnr = getPSRN(imagePath1, imagePath2);
			cout<<psnr<<endl;
		}
		else if(option == "-c"){
			if(argc != 4) throw("Faltan argumentos para -h, utilice help para mas info");
			string imagePath = argv[2];
			string tamLSB = argv[3];
			double capacity = getCapacity(imagePath, stoi(tamLSB));
			cout<<capacity<<endl;
		}
		else if(option == "-d"){
			if(argc != 4) throw("Faltan argumentos para -h, utilice help para mas info");
			string imagePath1 = argv[2];
			string imagePath2 = argv[3];
			display(imagePath1, imagePath2);
		}
		else if(option == "-k"){
			if(argc != 3) throw("Faltan argumentos para -h, utilice help para mas info");
			string imagePath = argv[2];
			displayStegoKey(imagePath);	
		}
		else throw("La opcion no existe, utilice help para mas info");
	}
	catch(string e){
		cout<<e<<endl;
	}
	catch(char const *e){
		cout<<e<<endl;
	}
	
}
