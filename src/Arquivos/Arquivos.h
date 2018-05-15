#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "../Estruturas/Item/Item.h"

#include <jsoncpp/json/json.h>
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

        std::map<std::string, std::map<std::string, double> > indiceInvertidoTfDocumentosPalavras;
        std::map<std::string, std::map<std::string, double> > indiceTfDocumentosPalavras;

        std::map<std::string, std::map<std::string, double> > vetorMedioPorUsuario;

        std::map<std::string, double> indiceIdfPalavras;

        std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > historicoUsuario;
        std::map<std::string, std::vector<std::string> > palavrasChaveDocumentos;
        std::map<std::string, std::map<std::string, double> > similaridades;
        std::map<std::string, std::shared_ptr<Json::Value> > biblioteca;

        std::vector<std::string> listaDocumentos, listaPalavras;

        std::vector<std::string> retornarListaIndicesDeMap(
            std::map<std::string, std::map<std::string, double> >&);
        
        // Métodos Estáticos
        static std::vector<std::string> split(const std::string&, const char);

        // Métodos
        std::tuple<std::string, std::string, double, time_t> parseAvaliacoes(std::string &);
        std::tuple<std::string, std::shared_ptr<Json::Value> > parseConteudo(std::string &);
        std::tuple<std::string, std::string> parseAlvos(const std::string&);

        std::vector<std::string> criarVetorPalavrasDoJson(Json::Value &);

        void calcularIdfPalavras(std::map<std::string, std::vector<std::string> >&, std::vector<std::string>&);
        void calcularTfDocumento(const std::string&, const std::vector<std::string>&);
        void calcularIdfPalavra(const std::vector<std::string>&);

        void construirInformacoesSobreItens(const std::string &);
        void construirHistoricoUsuarios(const std::string &);
        void construirVetorMedioUsuarios();

        void preProcessarDocumento(bool=true);

        void calcularSimilaridades();
        double calcularSimilaridadeItemAtualItensHistoricosUsuario(const std::string&, const std::string&);
        double calcularPredicaoAPartirVetorMedioUsuario(const std::string&, const std::string&);

        double retornarAmostraDistribuicaoDados(double, double);

        void pegarListaIndices();

        void predicao(const std::string&);
        double predizer(const std::string&, const std::string&);
    };
}

#endif
