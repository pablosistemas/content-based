#ifndef _UTIL_H
#define _UTIL_H

#include <jsoncpp/json/json.h>
#include <functional>
#include <set>

#include "../Estruturas/Item/Item.h"

using namespace Estruturas;

namespace Util {
    std::function<void(Json::Value *)> destrutor = [](Json::Value * p) {
        delete p;
    };

    std::function<void(Item *)> destrutorItem = [](Item* p) {
        delete p;
    };
}

#endif