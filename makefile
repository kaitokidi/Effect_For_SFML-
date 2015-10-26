# Makefile super op

all: main.o everything exe

main.o: *.cpp
	g++ -c *.cpp -std=c++11
	
everything:
	g++ -o exe *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -std=c++11
		
exe:
	./exe
	
clear:
	rm *.o
