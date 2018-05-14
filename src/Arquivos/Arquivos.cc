#include "../Algoritmos/StopWords/StopWords.h"
#include "../Algoritmos/Cosseno/Cosseno.h"
#include "../Algoritmos/TF-IDF/TfIdf.h"
#include "../Algoritmos/Dice/Dice.h"
#include "../Estruturas/Item/Item.h"
#include "../Util/Util.h"
#include "Arquivos.h"

#include <jsoncpp/json/json.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <memory>
#include <random>
#include <tuple>
#include <cmath>
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

    std::tuple<std::string, std::string> Content::parseAlvos(const std::string& linha) {
        auto stream = std::stringstream(linha);
        std::string usuarioId, itemId;
        std::getline(stream, usuarioId, ':');
        std::getline(stream, itemId, ',');
        return std::make_tuple (usuarioId, itemId);
    }

    void Content::preProcessarDocumento(bool usarPlot) {
        StopWords preprocessador;
        for (auto itm = biblioteca.begin(); itm != biblioteca.end(); itm++) {
            auto json = itm->second.get();
            string naoTokenizada = "";

            for (auto propriedade = Content::PROPRIEDADES_TEXTO_JSON.begin();
                propriedade != Content::PROPRIEDADES_TEXTO_JSON.end(); propriedade++){
                string temporaria = (*json)[*propriedade].asString();
                if(strcmp(temporaria.c_str(), "N/A") != 0)
                    naoTokenizada += " " + temporaria;
            }

            if (usarPlot) {
                naoTokenizada += (*json)["Plot"].asString();
            }
            const vector<string> tokens = split(naoTokenizada, ' ');
            palavrasChaveDocumentos[itm->first] = preprocessador.pipeline(tokens);
            calcularTfDocumento(itm->first, palavrasChaveDocumentos[itm->first]);
        }
    }

    void Content::calcularTfDocumento(
        const std::string &nomeDocumento,
        const std::vector<std::string>& vetorPalavras) {
        for (auto &&palavra : vetorPalavras) {
            auto tf = TfIdf::tf(vetorPalavras, palavra);
            indiceTfDocumentosPalavras[nomeDocumento].insert(
                std::pair<std::string, double>(
                    palavra, tf));
            indiceInvertidoTfDocumentosPalavras[palavra].insert(
                std::pair<std::string, double>(
                    nomeDocumento, tf));
        }
    }

    std::vector<std::string> Content::retornarListaIndicesDeMap(
        std::map<std::string, std::map<std::string, double> >& origemIndices) {
        std::vector<std::string> indices;
        indices.resize(origemIndices.size()); 
        size_t idx = 0;
        for (auto itm = origemIndices.begin(); itm != origemIndices.end(); itm++) {
            indices[idx++] = itm->first;
        }
        return indices;
    }

    void Content::calcularIdfPalavras(
        std::map<std::string, std::vector<std::string> >& palavrasChaveDocumentos,
        std::vector<std::string>& listaPalavras
    ) {
        std::map<std::string, double> listaIdfPalavras;
        for(auto itd = listaPalavras.begin(); itd != listaPalavras.end(); itd++) {
                listaIdfPalavras.insert(
                    std::pair<std::string, double>(*itd, TfIdf::idf(palavrasChaveDocumentos, *itd)));
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
        for (auto itm1 = biblioteca.begin(); itm1 != biblioteca.end(); itm1++) {
            for (auto itm2 = biblioteca.begin(); itm2 != biblioteca.end(); itm2++) {
                if (itm1->first != itm2->first) {
                    /*auto cossenoPlot = Cosseno::calcularSimilaridade(
                        this->indiceInvertidoTfDocumentosPalavras,
                        palavrasChaveDocumentos,
                        itm1->first,
                        itm2->first);*/
                    auto diceVetor = Dice::calcularCoeficiente(itm1->second, itm2->second);
                    //auto similaridade = (cossenoPlot + diceVetor) / 2.0;
                    auto similaridade = diceVetor;
                    similaridades[itm1->first][itm2->first] = similaridades[itm1->first][itm2->first] = similaridade;
                }
            }
        }
    }

    void Content::predicao(const std::string& caminho) {
        auto arquivo = std::ifstream (caminho);
        std::string linha;

        // descarta linha titulo
        std::getline(arquivo, linha, '\n');
        std::cout << "UserId:ItemId,Prediction" << std::endl;
        while(arquivo.good()){
            std::getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_usuario_item_id = parseAlvos(linha);
                auto predicao = predizer(
                    std::get<0>(par_usuario_item_id),
                    std::get<1>(par_usuario_item_id));
                std::cout << std::get<0>(par_usuario_item_id) << ":" << std::get<1>(par_usuario_item_id) << "," << predicao << std::endl;          
            }
        }
        arquivo.close();
    }

    double Content::predizer(const std::string& usuarioId, const std::string& itemId) {
        return calcularSimilaridadeItemAtualItensHistoricosUsuario(itemId, usuarioId);
    }

    double Content::calcularSimilaridadeItemAtualItensHistoricosUsuario(
        const std::string& itemId, const std::string& usuarioId) {
        if (biblioteca.count(itemId) == 0) {
            return retornarAmostraDistribuicaoDados(4.659206, 7.962903);
        }
        double num = 0;
        double den = 0;
        for(auto it = historicoUsuario[usuarioId].begin(); it != historicoUsuario[usuarioId].end(); it++) {
            if (similaridades[itemId].count(it->first) == 0) {
                auto similaridadeCosseno = Cosseno::calcularSimilaridade(
                    this->indiceInvertidoTfDocumentosPalavras,
                    palavrasChaveDocumentos,
                    itemId,
                    it->first);

                //auto similaridadeDice = Dice::calcularCoeficiente(biblioteca[itemId], biblioteca[it->first]);
                //auto similaridade = (similaridadeCosseno + similaridadeDice) / 2.0;
                auto similaridade = similaridadeCosseno;
                similaridades[itemId][it->first] = similaridades[itemId][it->first] = similaridade;
            }

            num += similaridades[itemId][it->first] * it->second.get()->avaliacao;
            den += similaridades[itemId][it->first];
        }
        if ((int)std::abs(den) == 0) { 
            // Use imdb rating
            return retornarAmostraDistribuicaoDados(4.659206, 7.962903);
        }
        return num/den;
    }

    double Content::retornarAmostraDistribuicaoDados(double shape, double scale) {
        std::default_random_engine gen;
        std::weibull_distribution<double> dist(shape, scale);
        return std::floor(dist(gen));
    }
}
