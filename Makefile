CC=g++
MAIN=src/main/main.cc
CFLAGS=-Wall -std=c++14
LDFLAGS=-ljsoncpp
OUTPUT=bin/recommender

all: recommender

recommender: $(MAIN)
	rm -rf bin || true
	mkdir bin
	$(CC) $(CFLAGS) \
	-g src/Algoritmos/StopWords/StopWords.cc \
	-g src/Algoritmos/Cosseno/Cosseno.cc \
	-g src/Algoritmos/TF-IDF/TfIdf.cc \
	-g src/Algoritmos/Dice/Dice.cc \
	-g src/Estruturas/Item/Item.cc \
	-g src/Arquivos/Arquivos.cc \
	$(MAIN) -o $(OUTPUT) $(LDFLAGS)
