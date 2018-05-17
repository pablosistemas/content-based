#include "Cosseno.h"

#include <algorithm>
#include <cmath>
#include <map>

namespace Algoritmos {
    double Cosseno::calcularSimilaridade(
        std::unordered_map<std::string, std::unordered_map<std::string, double> >& indicesTfInvertidos,
        std::unordered_map<std::string, std::vector<std::string> >& palavrasChaveDocumentos,
        std::unordered_map<std::string, double>& indiceIdfPalavras,
        const std::string& documento1,
        const std::string& documento2){
            double num, den1, den2;
            num = den1 = den2 = 0;
            for (auto itv = palavrasChaveDocumentos[documento1].cbegin();
                    itv != palavrasChaveDocumentos[documento1].cend(); itv++) {
                auto val1 = indicesTfInvertidos[*itv][documento1];
                auto val2 = 0.0;
                if (indicesTfInvertidos[*itv].count(documento2) > 0) {
                    val2 = indicesTfInvertidos[*itv][documento2];
                    auto tf = val1 * val2;
                    auto idf = (std::log(palavrasChaveDocumentos.size()/indiceIdfPalavras[*itv]));
                    num += (tf * idf * idf);
                }
                den1 += (val1 * val1);
                den2 += (val2 * val2); 
            }
            if (den1 == 0.0 || den2 == 0.0) { return 0; }
            auto similaridade = num / (std::sqrt(den1) * std::sqrt(den2));
            return similaridade;
    }    
}
