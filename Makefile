CC=g++
MAIN=src/main/main.cc
CFLAGS=-Wall -std=c++14
LDFLAGS=-ljsoncpp
OUTPUT=bin/recommender

all: recommender

recommender: $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $(OUTPUT) $(LDFLAGS) 