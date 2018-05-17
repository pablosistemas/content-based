CC=g++
MAIN=src/main/main.cc
CFLAGS=-Wall -std=c++14
JSONFLAGS=-Wno-deprecated-declarations
LDFLAGS=-ljsoncpp
OUTPUT=bin/recommender

JSONCPP_DIR=./jsoncpp

all: recommender

recommender: $(MAIN)
	echo "Certifique-se de JSONCPP estar instalado! Rode make install-jsoncpp como ROOT para instalar a biblioteca"
	rm -rf bin || true
	mkdir bin
	$(CC) \
	$(CFLAGS) \
	$(JSONFLAGS) \
	-g src/Algoritmos/StopWords/StopWords.cc \
	-g src/Algoritmos/Cosseno/Cosseno.cc \
	-g src/Algoritmos/TF-IDF/TfIdf.cc \
	-g src/Algoritmos/Dice/Dice.cc \
	-g src/Estruturas/Item/Item.cc \
	-g src/Arquivos/Arquivos.cc \
	-g src/Algoritmos/Preditor/Preditor.cc \
	-g src/Algoritmos/Similaridade/Similaridade.cc \
	-g src/Algoritmos/Estatistica/Estatistica.cc \
	-g jsoncpp/dist/jsoncpp.cpp \
	$(MAIN) \
	-L/usr/local/lib64 \
	-o $(OUTPUT)

recommender-jsoncpp-package-manager: $(MAIN)
	rm -rf bin || true
	mkdir bin
	$(CC) \
	$(CFLAGS) \
	$(LDFLAGS) \
	-g src/Algoritmos/StopWords/StopWords.cc \
	-g src/Algoritmos/Cosseno/Cosseno.cc \
	-g src/Algoritmos/TF-IDF/TfIdf.cc \
	-g src/Algoritmos/Dice/Dice.cc \
	-g src/Estruturas/Item/Item.cc \
	-g src/Arquivos/Arquivos.cc \
	$(MAIN) \
	-o $(OUTPUT)

install-jsoncpp:
	git clone https://github.com/open-source-parsers/jsoncpp.git
	mkdir $(JSONCPP_DIR)/build-src || true
	cd $(JSONCPP_DIR)/build-src && cmake .. && make && make install
	cd $(JSONCPP_DIR) && python amalgamate.py

run:
	$(OUTPUT) content.csv ratings.csv targets.csv > submission.csv

clean:
	rm bin/recommender || true

clean-jsoncpp:
	rm -rf jsoncpp || true
	rm -rf /usr/local/include/json || true
	rm -rf /usr/local/lib64/cmake/jsoncpp || true
	rm /usr/local/lib64/libjsoncpp.a || true
	rm /usr/local/lib64/pkgconfig/jsoncpp.pc || true
