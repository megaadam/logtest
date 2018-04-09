# For testing on an Orbit just use:
# docker-make
CC=g++ -std=c++14

default: 
	$(CC) -o logtest -pthread logtest.cpp LogProxy.cpp
