#include "Cosseno.h"

#include <algorithm>
#include <cmath>
#include <map>

namespace Algoritmos {
    double Cosseno::calcularSimilaridade(
        std::map<std::string, std::map<std::string, double> >& indicesInvertidos,
        std::map<std::string, std::vector<std::string> >& palavrasChaveDocumentos,
        const std::string& documento1,
        const std::string& documento2){
            double num, den1, den2;
            num = den1 = den2 = 0;
            for (auto itv = palavrasChaveDocumentos[documento1].cbegin();
                    itv != palavrasChaveDocumentos[documento1].cend(); itv++) {
                auto itv_par = std::find(palavrasChaveDocumentos[documento2].begin(),
                    palavrasChaveDocumentos[documento2].end(), *itv);
                if (itv_par != palavrasChaveDocumentos[documento2].end()) {
                    num += indicesInvertidos[*itv][documento1] * indicesInvertidos[*itv][documento2];
                    den1 += std::pow(indicesInvertidos[*itv][documento1], 2);
                    den2 += std::pow(indicesInvertidos[*itv][documento2], 2);
                }
            }
            if (den1 == 0) { return 0; }
            auto similaridade = num / (std::sqrt(den1) * std::sqrt(den2));
            return similaridade;
    }    
}
