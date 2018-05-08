#ifndef _UTIL_H
#define _UTIL_H

#include <jsoncpp/json/json.h>
#include <functional>

namespace Util {
    std::function<void(Json::Value *)> destrutor = [](Json::Value * p) {
        delete p;
    };
}

#endif