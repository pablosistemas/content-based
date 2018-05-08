#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <vector>
#include <string>

using namespace std;

namespace Algoritmos {
    struct StopWords {
        vector<string> stopWords;

        StopWords();

        vector<string> removerStopWordsDeDocumento(vector<string>&);

        bool compararSemCase(string&);
    };
}

#endif