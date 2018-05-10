#ifndef ITEM_H
#define ITEM_H

#include <time.h>

using namespace std;

namespace Estruturas {
    struct Item {
        Item(double, time_t);
        double tfIdf;
        double avaliacao;
        time_t timestamp;
    };
}

#endif
