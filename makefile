all: main abstractarea
	
main:
	g++ -Wall -o main main.cpp AbstractArea.cpp 

abstractarea:
	g++ -Wall -c AbstractArea.cpp

clean: 
	rm -f *~
	rm -f *.dat
	rm -f main
