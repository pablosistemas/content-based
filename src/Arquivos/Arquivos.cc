#include "../Algoritmos/Similaridade/Similaridade.h"
#include "../Algoritmos/StopWords/StopWords.h"
#include "../Algoritmos/Preditor/Preditor.h"
#include "../Algoritmos/Cosseno/Cosseno.h"
#include "../Algoritmos/TF-IDF/TfIdf.h"
#include "../Algoritmos/Dice/Dice.h"
#include "../Estruturas/Item/Item.h"
#include "../Util/Util.h"
#include "Arquivos.h"

#include <json/json.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>
#include <cmath>
#include <map>

using namespace std;
using namespace Algoritmos;
using namespace Estruturas;

namespace Arquivos {
    // Membros estáticos

    vector<string> Content::PROPRIEDADES_TEXTO_JSON;
    vector<string> Content::PROPRIEDADES_JSON;

    // Implementação métodos

    void Content::construirInformacoesSobreItens(const string& caminho) {
        auto arquivo = ifstream (caminho);
        string linha;

        // descarta linha titulo
        getline(arquivo, linha, '\n');
        while(arquivo.good()){
            getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_id_conteudo = parseConteudo(linha);

                biblioteca.insert(
                    pair<string, shared_ptr<Json::Value> >(
                        get<0>(par_id_conteudo),
                        get<1>(par_id_conteudo)
                    ));
            }
        }
        arquivo.close();
    }

    void Content::construirVetorMedioUsuarios() {

        for (auto it = historicoUsuario.begin(); it != historicoUsuario.end(); it++) {
            auto usuarioId = it->first;
            size_t numeroElementos = 0;

            for (auto itu = it->second.begin(); itu != it->second.end(); itu++) {
                auto itemId = itu->first;
                auto itemT = itu->second.get()->avaliacao;
                if (vetorMedioPorUsuario[usuarioId].count(itemId) == 0) {
                    vetorMedioPorUsuario[usuarioId][itemId] = itemT;
                } else {
                    vetorMedioPorUsuario[usuarioId][itemId] += itemT;
                }
                numeroElementos++;
            }

            for (auto itv = vetorMedioPorUsuario[usuarioId].begin(); itv != vetorMedioPorUsuario[usuarioId].end(); itv++) {
                itv->second = itv->second/numeroElementos;
            }
        }
    }

    void Content::construirHistoricoUsuarios(const string &caminho) {
        auto arquivo = ifstream (caminho);
        string linha;

        // descarta linha titulo
        getline(arquivo, linha, '\n');

        while(arquivo.good()){
            getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_usuario_item = parseAvaliacoes(linha);
                auto itemId = get<1>(par_usuario_item);
                auto usuarioId = get<0>(par_usuario_item);
                auto avaliacao = get<2>(par_usuario_item);
                auto timestamp = get<3>(par_usuario_item);

                if (historicoUsuario[usuarioId].count(itemId) == 0) {
                    shared_ptr<Item> ptr = shared_ptr<Item>(
                                    new Item(avaliacao, timestamp), Util::destrutorItem);
                    historicoUsuario[usuarioId].insert(
                        pair<string, shared_ptr<Item> >(
                            itemId,
                            shared_ptr<Item>(new Item(avaliacao, timestamp), Util::destrutorItem)));
                }
            }
        }
        arquivo.close();
    }

    tuple<string, shared_ptr<Json::Value> > Content::parseConteudo(string &linha) {
        Json::Reader leitor;
        auto stream = stringstream(linha);
        string item_id, imdb;
        getline(stream, item_id, ',');
        getline(stream, imdb, '\n');
        auto obj = new Json::Value();
        leitor.parse(imdb, *obj);
        return make_tuple (item_id, shared_ptr<Json::Value>(obj, Util::destrutor));
    }

    tuple<string, string, double, time_t> Content::parseAvaliacoes(string &linha) {
        Json::Reader leitor;
        auto stream = stringstream(linha);
        string usuarioId, itemId, rating, timestamp;
        getline(stream, usuarioId, ':');
        getline(stream, itemId, ',');
        getline(stream, rating, ',');
        getline(stream, timestamp, '\n');
        return make_tuple (usuarioId, itemId, strtod(rating.c_str(), NULL), strtol(timestamp.c_str(), NULL, 10));
    }

    tuple<string, string> Content::parseAlvos(const string& linha) {
        auto stream = stringstream(linha);
        string usuarioId, itemId;
        getline(stream, usuarioId, ':');
        getline(stream, itemId, ',');
        return make_tuple (usuarioId, itemId);
    }

    void Content::preProcessarDocumento(bool usarPlot) {
        StopWords preprocessador;
        for (auto itm = biblioteca.begin(); itm != biblioteca.end(); itm++) {
            auto json = itm->second.get();
            string naoTokenizada;

            for (auto propriedade = Content::PROPRIEDADES_TEXTO_JSON.begin();
                propriedade != Content::PROPRIEDADES_TEXTO_JSON.end(); propriedade++){
                string temporaria = (*json)[*propriedade].asString();
                if(strcmp(temporaria.c_str(), "N/A") != 0) {
                    if (naoTokenizada.size() > 0)
                        naoTokenizada += " " + temporaria;
                    else 
                        naoTokenizada = temporaria;
                }
            }

            vector<string> tokens = split(naoTokenizada, ' ');
            palavrasChaveDocumentos[itm->first] = preprocessador.pipeline(tokens);
            calcularTfDocumento(itm->first, palavrasChaveDocumentos[itm->first]);

            if (usarPlot) {
                auto plotTemporario = (*json)["Plot"].asString();
                if(strcmp(plotTemporario.c_str(), "N/A") != 0) {
                    naoTokenizada = plotTemporario;
                    tokens = split(naoTokenizada, ' ');
                    auto plotTokenizado = preprocessador.pipeline(tokens);
                    plotTokenizado = calcularTfDocumento(itm->first, plotTokenizado, 10);
                    auto itv = palavrasChaveDocumentos[itm->first].begin() + palavrasChaveDocumentos[itm->first].size();
                    palavrasChaveDocumentos[itm->first].insert(itv, plotTokenizado.begin(), plotTokenizado.end());
                }
            }

            calcularIdfPalavra(palavrasChaveDocumentos[itm->first]);
        }
    }

    bool Content::insereEmIndicesTf(const string& nomeDocumento, const string& palavra, double tf) {
        if (indiceTfDocumentosPalavras[nomeDocumento].count(palavra) == 0) {
            indiceTfDocumentosPalavras[nomeDocumento].insert(
                pair<string, double>(
                    palavra, tf));
            indiceInvertidoTfDocumentosPalavras[palavra].insert(
                pair<string, double>(
                    nomeDocumento, tf));
            return true;
        } else {
            indiceTfDocumentosPalavras[nomeDocumento][palavra] = max(
                tf,
                indiceTfDocumentosPalavras[nomeDocumento][palavra]);
            indiceInvertidoTfDocumentosPalavras[palavra][nomeDocumento] = max(
                tf,
                indiceInvertidoTfDocumentosPalavras[palavra][nomeDocumento]);
            return false;
        }
    }

    vector<string> Content::calcularTfDocumento(
        const string &nomeDocumento,
        const vector<string>& vetorPalavras, int K) {
        vector<string> vetorPalavrasFrequentes;
        if (K == -1) {
            for (auto &&palavra : vetorPalavras) {
                auto tf = TfIdf::tf(vetorPalavras, palavra);
                if (insereEmIndicesTf(nomeDocumento, palavra, tf)) {
                    vetorPalavrasFrequentes.push_back(palavra);
                }
            }
            return vetorPalavras;
        } else {
            map<double, string> palavrasMaisFrequentes;
            for (auto &&palavra : vetorPalavras) {
                auto tf = TfIdf::tf(vetorPalavras, palavra);
                palavrasMaisFrequentes.insert(
                    pair<double, string>(
                        tf, palavra));
            }
            auto itm = palavrasMaisFrequentes.begin();
            int k = 0;
            vector<string> vetorPalavrasFrequentes; //(min((size_t)K, palavrasMaisFrequentes.size()));
            while (k < K && itm != palavrasMaisFrequentes.end()) {
                if (insereEmIndicesTf(nomeDocumento, itm->second, itm->first)) {
                    vetorPalavrasFrequentes.push_back(itm->second);
                }
                itm++;
            }
            return vetorPalavrasFrequentes;
        }
    }

    vector<string> Content::retornarListaIndicesDeMap(
        unordered_map<string, unordered_map<string, double> >& origemIndices) {
        vector<string> indices;
        indices.resize(origemIndices.size()); 
        size_t idx = 0;
        for (auto itm = origemIndices.begin(); itm != origemIndices.end(); itm++) {
            indices[idx++] = itm->first;
        }
        return indices;
    }

    void Content::calcularIdfPalavras(
        unordered_map<string, vector<string> >& palavrasChaveDocumentos,
        vector<string>& listaPalavras
    ) {
        map<string, double> listaIdfPalavras;
        for(auto itd = listaPalavras.begin(); itd != listaPalavras.end(); itd++) {
                listaIdfPalavras.insert(
                    pair<string, double>(*itd, TfIdf::idf(palavrasChaveDocumentos, *itd)));
        }
    }

    void Content::calcularIdfPalavra(const vector<string>& palavras) {
        for (auto palavra = palavras.begin(); palavra != palavras.end(); palavra++) {
            if (indiceIdfPalavras.count(*palavra) == 0) {
                indiceIdfPalavras[*palavra] = 1;
            } else {
                indiceIdfPalavras[*palavra]++;
            }
        }
    }

    vector<string> Content::split(const string& texto, const char delimitador) {
        vector<string> tokens;
        size_t prox = -1;
        do {
            size_t atual = prox + 1;
            prox = texto.find_first_of(delimitador, atual);
            tokens.push_back(texto.substr(atual, (prox - atual)));
        } while(prox != string::npos);
        return tokens;
    }

    void Content::predicao(const string& caminho) {
        auto arquivo = ifstream (caminho);
        string linha;

        // descarta linha titulo
        getline(arquivo, linha, '\n');
        cout << "UserId:ItemId,Prediction" << endl;
        while(arquivo.good()){
            getline(arquivo, linha, '\n');
            if (linha != "") {
                auto par_usuario_item_id = parseAlvos(linha);
                auto predicao = Preditor::predizer(
                    historicoUsuario,
                    indiceInvertidoTfDocumentosPalavras,
                    similaridades,
                    biblioteca,
                    palavrasChaveDocumentos,
                    indiceIdfPalavras,
                    get<0>(par_usuario_item_id),
                    get<1>(par_usuario_item_id));
                cout << get<0>(par_usuario_item_id) << ":" << get<1>(par_usuario_item_id) << "," << predicao << endl;          
            }
        }
        arquivo.close();
    }
}
