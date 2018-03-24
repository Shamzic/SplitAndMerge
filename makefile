
CFLAGS= -Werror -Wall

all:  abstractarea area main
	
main:
	g++ -Wall -o main -lstdc++ main.cpp Area.cpp AbstractArea.cpp $(CFLAGS)

abstractarea:
	g++ -Wall -c AbstractArea.cpp $(CFLAGS)

area:
	g++ -Wall -c Area.cpp $(CFLAGS)

clean: 
	rm -f *~
	rm -f *.dat
	rm -f main
	rm -f abstractarea
	rm -f area