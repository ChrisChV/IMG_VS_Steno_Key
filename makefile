
testVS:
	g++ -g -std=c++17 -o Test/runTestVs Test/testVS.cpp VS/VS.o Utils/Utils.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

testSteno:
	g++ -g -std=c++17 -o Test/runTestSteno Test/testSteno.cpp Steno/Steno.o Utils/Utils.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

testSteno2:
	g++ -g -std=c++17 -o Test/runTestSteno2 Test/testSteno2.cpp Steno/Steno.o VS/VS.o Utils/Utils.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

testRC4:
	g++ -g -std=c++17 -o Test/runTestRC4 Test/testRC4.cpp

main:
	g++ -g -std=c++17 -o Main/runMain Main/main.cpp Steno/Steno.o VS/VS.o Utils/Utils.o Interface/interface.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11



interface:
	g++ -g -c -std=c++17 Interface/interface.cpp -o Interface/interface.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	make main

vs:
	g++ -g -c -std=c++17 VS/VS.cpp -o VS/VS.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	make testVS
	make testSteno2
	make interface

steno:
	g++ -g -c -std=c++17 Steno/Steno.cpp -o Steno/Steno.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	make testSteno
	make testSteno2
	make interface

utils:
	g++ -g -c -std=c++17 Utils/Utils.cpp -o Utils/Utils.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	make vs
	make steno

all:
	make vs
	make steno
	make utils
	make interface
	make testVS
	make testSteno
	make testRC4