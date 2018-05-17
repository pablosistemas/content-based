#ifndef DICE_H
#define DICE_H

#include <json/json.h>
#include <memory>
#include <map>

namespace Algoritmos {
    struct Dice {
        static double calcularCoeficiente(
            std::shared_ptr<Json::Value>&,
            std::shared_ptr<Json::Value>&);
    };
}

#endif
