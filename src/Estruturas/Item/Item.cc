#include "Item.h"

namespace Estruturas {
    Item::Item(double avaliacao, time_t timestamp) {
        this->avaliacao = avaliacao;
        this->timestamp = timestamp;
    }
}
