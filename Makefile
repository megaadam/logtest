CC=g++ -std=c++14

default: 
	$(CC) -o logtest -pthread testStr.cpp LogP.cpp
