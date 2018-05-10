#ifndef COSSENO_H
#define COSSENO_H

#include <jsoncpp/json/json.h>

namespace Algoritmos {
    struct Cosseno {
        static double calcularSimilaridade(Json::Value &, Json::Value&);
    };
}

#endif
