#include "../Algoritmos/StopWords/StopWords.h"
#include "../Algoritmos/TF-IDF/TfIdf.h"
#include "../Estruturas/Item/Item.h"
#include "../Util/Util.h"
#include "Arquivos.h"

#include <jsoncpp/json/json.h>
#include <fstream>
#include <sstream>
#include <tuple>
#include <map>

using namespace Algoritmos;
using namespace Estruturas;

namespace Arquivos {
    // Membros estáticos
    std::vector<std::string> Content::PROPRIEDADES_TEXTO_JSON;
    std::vector<std::string> Content::PROPRIEDADES_JSON;

    // Implementação métodos
    void Content::lerInformacoesSobreItens(const std::string& caminho) {
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

    void Content::lerHistoricoUsuarios(const std::string &caminho) {
        auto arquivo = std::ifstream (caminho);
        std::string linha;

        // descarta linha titulo
        std::getline(arquivo, linha, '\n');
        while(arquivo.good()){
            std::getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_usuario_item = parseAvaliacoes(linha);
                auto itemId = std::get<1>(par_usuario_item);
                auto usuarioId = std::get<0>(par_usuario_item);
                auto avaliacao = std::get<2>(par_usuario_item);
                auto timestamp = std::get<3>(par_usuario_item);

                if (historicoUsuario[usuarioId].count(itemId) == 0) {
                    std::shared_ptr<Item> ptr = std::shared_ptr<Item>(
                                    new Item(avaliacao, timestamp), Util::destrutorItem);
                    historicoUsuario[usuarioId].insert(
                        std::pair<std::string, std::shared_ptr<Item> >(
                            itemId,
                            std::shared_ptr<Item>(new Item(avaliacao, timestamp), Util::destrutorItem)));
                }
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

    std::tuple<std::string, std::string, double, time_t> Content::parseAvaliacoes(std::string &linha) {
        Json::Reader leitor;
        auto stream = std::stringstream(linha);
        std::string usuarioId, itemId, rating, timestamp;
        std::getline(stream, usuarioId, ':');
        std::getline(stream, itemId, ',');
        std::getline(stream, rating, ',');
        std::getline(stream, timestamp, '\n');
        return std::make_tuple (usuarioId, itemId, strtod(rating.c_str(), NULL), strtol(timestamp.c_str(), NULL, 10));
    }

    void Content::preProcessarDocumento() {
        StopWords preprocessador;
        for (auto itm = biblioteca.begin(); itm != biblioteca.end(); itm++) {
            auto json = *itm->second.get();

            for (auto itp = Content::PROPRIEDADES_TEXTO_JSON.begin();
                itp != Content::PROPRIEDADES_TEXTO_JSON.end(); itp++) {
                Json::Value &jsonParsed;
                const string plot = json[*itp].asString();
                const vector<string> tokens = split(plot, ' ');
                auto novoPlot = preprocessador.pipeline(tokens);
                calcularTfDocumento(itm->first, json);
            }
        }
    }

    void Content::calcularTfDocumento(const std::string &nomeDocumento, Json::Value &json) {
        auto doc = criarVetorPalavrasDoJson(json);
        for (auto &&palavra : doc) {
            tfPorDocumento[nomeDocumento].insert(std::pair<std::string, double>(palavra, TfIdf::tf(doc, palavra)));
        }
    }

    std::vector<std::string> Content::criarVetorPalavrasDoJson(Json::Value &json) {
        std::vector<std::string> palavras;
        for (auto itp = Content::PROPRIEDADES_TEXTO_JSON.begin();
            itp != Content::PROPRIEDADES_TEXTO_JSON.end(); itp++) {
                
        }
    }

    vector<string> Content::split(const string& texto, const char delimitador) {
        vector<string> tokens;
        size_t prox = -1;
        do {
            size_t atual = prox + 1;
            prox = texto.find_first_of(delimitador, atual);
            tokens.push_back(texto.substr(atual, (prox - atual)));
        } while(prox != std::string::npos);
        return tokens;
    }

    void Content::calcularSimilaridades() {
        for (auto itm = biblioteca.begin(); itm != biblioteca.end(); itm++) {
            for (auto itm2 = biblioteca.begin(); itm2 != biblioteca.end(); itm2++) {
                if (itm->first == itm2->first) { continue; }
                calcularCosseno(*itm->second.get(), *itm2->second.get());
            }
        }
    }

}
