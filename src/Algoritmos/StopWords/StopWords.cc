#include "StopWords.h"

#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
#include <string>

using namespace std;

namespace Algoritmos {

    bool StopWords::compararSemCase(string& pal1) {
        for (auto &&pal2 : stopWords) {
            if (strcasecmp(pal1.c_str(), pal2.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    StopWords::StopWords() {
        ifstream fp;
        fp.open("../../../data/stop_words_english.txt");
        if (fp.is_open()) {
            cout << strerror(errno) << endl;
        }
        
        vector<string> stopWords;
        string palavra;

        while(getline(fp, palavra)) {
            stopWords.push_back(palavra);
        }

        fp.close();
    }

    vector<string> StopWords::removerStopWordsDeDocumento(vector<string>& doc) {
        vector<string> docFiltrado;
        for (auto &&palavra : doc) {
            if(compararSemCase(palavra) == false) {
                docFiltrado.push_back(palavra);
            }
        }
        return docFiltrado;
    }
}