songs.out : main.o song.o
	g++ -Wall -ansi -g -o songs.out song.o main.o

song.o : song.cpp song.h
	g++ -Wall -ansi -g -c song.cpp

main.o : main.cpp song.h
	g++ -Wall -ansi -g -c main.cpp

clean : 
	rm -rf  songs.out  song.o  main.o
