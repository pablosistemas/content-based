#include "../Util/Util.h"
#include "Arquivos.h"

#include <jsoncpp/json/json.h>
#include <fstream>
#include <sstream>
#include <tuple>
#include <map>

namespace Arquivos {
    void Content::lerInformacoesSobreItens(std::string& caminho) {
        auto arquivo = std::ifstream (caminho);
        std::string linha;

        // descarta linha titulo
        std::getline(arquivo, linha, '\n');
        while(arquivo.good()){
            std::getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_id_conteudo = parseConteudo(linha);

                biblioteca.insert(
                    std::pair<std::string, std::shared_ptr<Json::Value> >(
                        std::get<0>(par_id_conteudo),
                        std::get<1>(par_id_conteudo)
                    ));
            }
        }
        arquivo.close();
    }

    std::tuple<std::string, std::shared_ptr<Json::Value> > Content::parseConteudo(std::string &linha) {
        Json::Reader leitor;
        auto stream = std::stringstream(linha);
        std::string item_id, imdb;
        std::getline(stream, item_id, ',');
        std::getline(stream, imdb, '\n');
        auto obj = new Json::Value();
        leitor.parse(imdb, *obj);
        return std::make_tuple (item_id, std::shared_ptr<Json::Value>(obj, Util::destrutor));
    }
}
