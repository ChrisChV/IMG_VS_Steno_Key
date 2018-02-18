#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include "../Utils/sad.h"
#include "../Steno/Steno.h"
#include "../VS/VS.h"

using namespace std;

string hide(string msgPath, string imagePath, int tamLSB);
string reveal(string imagePath, int tamLSB);
double getPSRN(string imagePath1, string imagePath2);
double getCapacity(string imagePath, int tamLSB);
void display(string imagePath1, string imagePath2);
void displayStegoKey(string imagePath);

#endif