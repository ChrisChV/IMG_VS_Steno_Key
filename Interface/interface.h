#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include "../Steno/Steno.h"
#include "../VS/VS.h"

using namespace std;

string hide(string msgPath, string imagePath);
string reveal(string imagePath);
double getPSRN(string imagePath1, string imagePath2);


#endif