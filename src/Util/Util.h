#ifndef _UTIL_H
#define _UTIL_H

#include <json/json.h>
#include <functional>
#include <random>
#include <cmath>
#include <set>

#include "../Estruturas/Item/Item.h"

using namespace std;
using namespace Estruturas;

namespace Util {
    function<void(Json::Value *)> destrutor = [](Json::Value * p) {
        delete p;
    };

    function<void(Item *)> destrutorItem = [](Item* p) {
        delete p;
    };

}

#endif