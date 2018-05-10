#include "StopWords.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <string.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

namespace Algoritmos {

    bool StopWords::compararStopWordsComCase(const string& pal1) {
        for (auto &&pal2 : stopWords) {
            if (strcasecmp(pal1.c_str(), pal2.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    bool StopWords::compararStopWordsSemCase(const string& pal1) {
        for (auto &&pal2 : stopWords) {
            if (strcmp(pal1.c_str(), pal2.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    StopWords::StopWords() {
        // TODO: Preprocessar stopwords para evitar comparar you're por youre, por exemplo

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

    vector<string> StopWords::pipeline(const vector<string>& doc) {
        vector<string> docFiltrado;
        std::map<std::string, double> indice_idf_palavras;

        for (auto &&palavra : doc) {
            // padronizar case para minúscula
            // remover acentuacao, pontuacao
            // remover stop words
            auto palavraModificada = mudarCasePalavraMinuscula(palavra);
            if (palavraModificada != "") {
                bool inserirPalavra = !compararStopWordsSemCase(palavra);
                if (inserirPalavra) { docFiltrado.push_back(palavra); }
            }
        }
        return docFiltrado;
    }

    std::string StopWords::mudarCasePalavraMinuscula(const string &palavra) {
        string palavraModificada;
        palavraModificada.reserve(palavra.size());

        for (size_t i = 0; i < palavra.size(); i++) {
            char caractere = retornaCaractereNaoAcentuado(palavra[i]);
            // Caractere entre 'A' e 'Z'
            if (!((caractere >= 'A' && caractere <= 'Z') || (caractere >= 'a' && caractere <= 'z'))) { 
                continue; 
            }
            if (caractere < 0x5b && caractere > 40)  {
                caractere += ('a' - 'A');
            }
            palavraModificada.push_back(caractere);
        }
        return palavraModificada;
    }

    char StopWords::retornaCaractereNaoAcentuado(const char caractere) {
        char *p_Char = (char *)memchr(ACCENT_CHARS, caractere, sizeof(ACCENT_CHARS));
        return (p_Char ? UNACCENT_CHARS[(p_Char - ACCENT_CHARS)] : caractere);
    }
}