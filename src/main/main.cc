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
        "Genre", "Director", "Writer", "Actors", "Language", "Country", "Awards" };

    conteudo.construirInformacoesSobreItens(std::string(argv[1]));

    conteudo.preProcessarDocumento(false);

    conteudo.construirHistoricoUsuarios(std::string(argv[2]));

    conteudo.listaPalavras = conteudo.retornarListaIndicesDeMap(conteudo.indiceInvertidoTfDocumentosPalavras);

    conteudo.predicao(argv[3]);

}
