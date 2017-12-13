vs:
	g++ -g -c -std=c++17 VS/VS.cpp -o VS/VS.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

steno:
	g++ -g -c -std=c++17 Steno/Steno.cpp -o Steno/Steno.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

testVS:
	g++ -g -std=c++17 -o Test/runTestVs Test/testVS.cpp VS/VS.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

testSteno:
	g++ -g -std=c++17 -o Test/runTestSteno Test/testSteno.cpp Steno/Steno.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11