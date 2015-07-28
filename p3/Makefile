funix.out : directory.o funix.o main.o permissions.o  
	g++ -ansi -Wall -g  -o funix.out directory.o funix.o main.o permissions.o  

directory.o : directory.cpp directory.h permissions.h 
	g++ -ansi -Wall -g  -c directory.cpp

funix.o : funix.cpp funix.h directory.h 
	g++ -ansi -Wall -g  -c funix.cpp

main.o : main.cpp funix.h 
	g++ -ansi -Wall -g  -c main.cpp

permissions.o : permissions.cpp permissions.h 
	g++ -ansi -Wall -g  -c permissions.cpp

clean : 
	rm -f funix.out directory.o  funix.o  main.o  permissions.o   
