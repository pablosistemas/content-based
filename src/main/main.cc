#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>

#include "../Arquivos/Arquivos.h"
#include "../Algoritmos/StopWords/StopWords.h"

using namespace Arquivos;
using namespace Algoritmos;

int main (int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }

    Content conteudo;
    std::string caminho = std::string(argv[1]);
    conteudo.lerInformacoesSobreItens(caminho);

    StopWords preProcessador;

    vector<string> texto;
    preProcessador.removerStopWordsDeDocumento(texto);
    
}

/*
std::ifstream ifs(argv[1]);
    Json::Reader leitor;
    Json::Value obj;

    leitor.parse(ifs, obj);
    std::cout << "Book: " << obj["book"].asString() << std::endl;
    std::cout << "Year: " << obj["year"].asUInt() << std::endl;
    const Json::Value& characters = obj["characters"]; // array of characters
    for (int i = 0; i < characters.size(); i++){
        std::cout << "    name: " << characters[i]["name"].asString();
        std::cout << " chapter: " << characters[i]["chapter"].asUInt();
        std::cout << std::endl;
    }
*/
