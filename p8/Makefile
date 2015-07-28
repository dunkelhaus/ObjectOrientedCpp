all : p8.out p8b.out

p8.out : main.cpp SVector.cpp SVector.h
	g++ -Wall -ansi -g -DNDEBUG main.cpp -o p8.out

p8b.out : main.cpp SVector.cpp SVector.h
	g++ -Wall -ansi -g main.cpp -o p8b.out

clean : 
	rm -f  p8.out  p8b.out
