#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <vector>
#include <string>

using namespace std;

namespace Algoritmos {


    #define ACCENT_CHARS    "ÁÀÃÂÇáàãâçÉÊéêÍíÑÓÔÕñóôõÚÜúü"
    #define UNACCENT_CHARS  "AAAACaaaacEEeeIiNOOOnoooUUuu"

    struct StopWords {
        vector<string> stopWords;

        StopWords();

        vector<string> pipeline(const vector<string>&);

        // Métodos Pipeline
        std::string mudarCasePalavraMinuscula(const std::string &);
        char retornaCaractereNaoAcentuado(const char);
        bool compararStopWordsSemCase(const string&);
        bool compararStopWordsComCase(const string&);
    };
}

#endif