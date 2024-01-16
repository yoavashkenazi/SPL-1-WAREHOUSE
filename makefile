
all: clean compile link

link:
	g++ -o bin/hello bin/main.o bin/someclass.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/someclass.o src/someclass.cpp

clean:
	rm -f bin/*
