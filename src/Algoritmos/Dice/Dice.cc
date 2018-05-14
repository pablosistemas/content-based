#include <string.h>

#include "../../Arquivos/Arquivos.h"
#include "Dice.h"

using namespace Arquivos;

namespace Algoritmos {
    double Dice::calcularCoeficiente(
                std::shared_ptr<Json::Value>& p1,
                std::shared_ptr<Json::Value>& p2) {
        double interseccao_palavras_chave = 0;
        for (auto propriedade = Content::PROPRIEDADES_TEXTO_JSON.begin();
                propriedade != Content::PROPRIEDADES_TEXTO_JSON.end(); propriedade++){
            std::string propDoc1 = (*p1.get())[*propriedade].asString();       
            std::string propDoc2 = (*p2.get())[*propriedade].asString();       
            // compara apenas propriedades nao "N/A"
            if (strcmp(propDoc1.c_str(), "N/A") != 0 && strcmp(propDoc2.c_str(), "N/A") != 0) {
                if (strcmp(propDoc1.c_str(), propDoc2.c_str()) == 0) {
                    interseccao_palavras_chave++;
                }
            }
        }
        return interseccao_palavras_chave/(Content::PROPRIEDADES_TEXTO_JSON.size()); // 2/2 implicito
    }
}