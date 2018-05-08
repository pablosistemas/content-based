#ifndef _ARQUIVOS_H
#define _ARQUIVOS_H

#include <jsoncpp/json/json.h>
#include <memory>
#include <map>

namespace Arquivos {
    struct Content {
        std::map<std::string, std::shared_ptr<Json::Value> > biblioteca;

        void lerInformacoesSobreItens(std::string &);

        std::tuple<std::string, std::shared_ptr<Json::Value> > parseConteudo(std::string &);
    };
}

#endif