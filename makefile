# Makefile super op

all: main.o everything exe

main.o: *.cpp
	g++ -c *.cpp	
	
everything:
	g++ -o exe *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
		
exe:
	./exe
	
clear:
	rm *.o
