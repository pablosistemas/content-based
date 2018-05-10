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

        std::map<std::string, std::shared_ptr<Json::Value> > biblioteca;
        std::map<std::string, std::map<std::string, std::shared_ptr<Item> > > historicoUsuario;
        std::map<std::string, std::map<std::string, std::vector<std::string> > > topicosDocumentos;

        static std::map<std::string, double> indiceIdfPalavras;
        static std::map<std::string, std::map<std::string, double> > similaridades;
        static std::map<std::string, std::map<std::string, double> > tfPorDocumento;


        // Métodos
        std::tuple<std::string, std::string, double, time_t> parseAvaliacoes(std::string &);
        std::tuple<std::string, std::shared_ptr<Json::Value> > parseConteudo(std::string &);
        std::vector<std::string> criarVetorPalavrasDoJson(Json::Value &);
        std::vector<std::string> split(const std::string&, const char);
        void lerInformacoesSobreItens(const std::string &);
        void lerHistoricoUsuarios(const std::string &);
        void calcularTfDocumento(const std::string &, Json::Value &);
        void preProcessarDocumento();
        void calcularSimilaridades();

    };
}

#endif
