main: main.cpp query.o
	g++ main.cpp query.o -o main -std=c++11 -g

query.o:query.cpp
	g++ query.cpp -c -o query.o -std=c++11

clean:
	rm main *.o
