#ifndef COSSENO_H
#define COSSENO_H

#include "../../Estruturas/Item/Item.h"
#include <jsoncpp/json/json.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <map>

namespace Algoritmos {
    struct Cosseno {
        static double calcularSimilaridade(
            std::unordered_map<std::string, std::unordered_map<std::string, double> >&,
            std::unordered_map<std::string, std::vector<std::string> >&,
            std::unordered_map<std::string, double>&,
            const std::string&,
            const std::string&);
    };
}

#endif
