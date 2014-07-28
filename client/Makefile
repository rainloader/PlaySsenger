#temp
main : main.o
	g++ -o main main.o $(shell ls ../common/*.o)
main.o : main.cpp
	g++ -c main.cpp

clean :
	rm main.o
