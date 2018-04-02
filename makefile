CC=g++ 
CFLAGS= -g -Wall
LDFLAGS=
LIBS = 

MAIN_O = LeafArea.o Area.o AbstractArea.o image_ppm.o main.o
all:   main

%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $(LDFLAGS) $@ $< $(LIBS)

main: $(MAIN_O)
	g++ $(CFLAGS) $^ -o $@


clean: 
	rm -f *.o
	rm -f *.dat
	