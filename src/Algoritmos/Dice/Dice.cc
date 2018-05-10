#include <string.h>

#include "../../Arquivos/Arquivos.h"
#include "Dice.h"

using namespace Arquivos;

namespace Algoritmos {
    double Dice::calcularCoeficiente(
                std::shared_ptr<Json::Value>& p1,
                std::shared_ptr<Json::Value>& p2) {
        double interseccao_palavras_chave = 0;
        for (auto propriedade = Content::PROPRIEDADES_JSON.begin();
                propriedade != Content::PROPRIEDADES_JSON.end(); propriedade++){
            if (strcmp((*p1.get())[*propriedade].asString().c_str(), (*p2.get())[*propriedade].asString().c_str()) == 0) {
                interseccao_palavras_chave++;
            }
        }

        return interseccao_palavras_chave/(Content::PROPRIEDADES_JSON.size()); // 2/2 implicito
    }
}