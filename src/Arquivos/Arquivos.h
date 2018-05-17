#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "../Estruturas/Item/Item.h"

#include <json/json.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include <map>
#include <set>

using namespace Estruturas;

namespace Arquivos {
    struct Content {

        // Propriedades
        static std::vector<std::string> PROPRIEDADES_JSON;
        static std::vector<std::string> PROPRIEDADES_TEXTO_JSON;

        std::unordered_map<std::string, std::unordered_map<std::string, double> > indiceInvertidoTfDocumentosPalavras;
        std::unordered_map<std::string, std::unordered_map<std::string, double> > indiceTfDocumentosPalavras;

        std::unordered_map<std::string, std::unordered_map<std::string, double> > vetorMedioPorUsuario;

        std::unordered_map<std::string, double> indiceIdfPalavras;

        std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Item> > > historicoUsuario;
        std::unordered_map<std::string, std::vector<std::string> > palavrasChaveDocumentos;
        std::unordered_map<std::string, std::unordered_map<std::string, double> > similaridades;
        std::unordered_map<std::string, std::shared_ptr<Json::Value> > biblioteca;

        std::vector<std::string> listaDocumentos, listaPalavras;

        std::vector<std::string> retornarListaIndicesDeMap(
            std::unordered_map<std::string, std::unordered_map<std::string, double> >&);
        
        // Métodos Estáticos
        static std::vector<std::string> split(const std::string&, const char);

        // Métodos
        std::tuple<std::string, std::string, double, time_t> parseAvaliacoes(std::string &);
        std::tuple<std::string, std::shared_ptr<Json::Value> > parseConteudo(std::string &);
        std::tuple<std::string, std::string> parseAlvos(const std::string&);

        std::vector<std::string> criarVetorPalavrasDoJson(Json::Value &);

        void calcularIdfPalavras(std::unordered_map<std::string, std::vector<std::string> >&, std::vector<std::string>&);
        std::vector<std::string> calcularTfDocumento(const std::string&, const std::vector<std::string>&, int=-1);
        void calcularIdfPalavra(const std::vector<std::string>&);

        void construirInformacoesSobreItens(const std::string &);
        void construirHistoricoUsuarios(const std::string &);
        void construirVetorMedioUsuarios();

        void preProcessarDocumento(bool=true);

        void calcularSimilaridades();
        double calcularSimilaridadeItemAtualItensHistoricosUsuario(const std::string&, const std::string&);
        double calcularPredicaoAPartirVetorMedioUsuario(const std::string&, const std::string&);

        void pegarListaIndices();

        bool insereEmIndicesTf(const std::string&, const std::string&, double);

        void predicao(const std::string&);
        double predizer(const std::string&, const std::string&);
    };
}

#endif
