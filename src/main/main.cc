#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>

#include "../Arquivos/Arquivos.h"

using namespace Arquivos;

int main (int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }

    Content conteudo;

    Content::PROPRIEDADES_JSON = std::vector<std::string> {
            "Title", "Year", "Rated", "Released", "Runtime", "Genre", "Director", "Writer", "Actors", "Plot",
            "Language", "Country", "Awards", "Poster", "Metascore", "imdbRating", "imdbVotes"
        };

    Content::PROPRIEDADES_TEXTO_JSON = std::vector<std::string> {
            "Title", "Genre", "Director", "Writer", "Actors", "Plot",
            "Language", "Country", "Awards"
        };

    conteudo.lerInformacoesSobreItens(std::string(argv[1]));
    conteudo.preProcessarDocumento();
    conteudo.lerHistoricoUsuarios(std::string(argv[2]));
    conteudo.calcularSimilaridades();
}


    /*std::ifstream ifs("data/content.csv");
    Json::Reader leitor;
    Json::Value obj;
    std::string itemid, json, linha;
    getline(ifs, linha, '\n');
    getline(ifs, itemid, ',');
    getline(ifs, json, '\n');

    leitor.parse(json, obj);
    std::cout << "Book: " << obj["Title"].asString() << std::endl;
    std::cout << "Year: " << obj["Year"].asString() << std::endl;
    const Json::Value& characters = obj["Plot"]; // array of characters
    std::cout << "Plot: " << obj["Plot"].asString() << std::endl;
    for (int i = 0; i < characters.size(); i++){
        std::cout << "    name: " << characters[i]["name"].asString();
        std::cout << " chapter: " << characters[i]["chapter"].asUInt();
        std::cout << std::endl;
    }
}*/
