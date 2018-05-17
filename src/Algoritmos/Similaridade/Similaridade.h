#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include <unordered_map>
#include <json/json.h>
#include <iostream>
#include <memory>
#include <vector>

#include "../../Estruturas/Item/Item.h"
#include "../Estatistica/Estatistica.h"

using namespace std;
using namespace Estruturas;

namespace Algoritmos {
    struct Similaridade {
        static double calcularSimilaridadeItemAtualItensHistoricosUsuario(
            unordered_map<string, unordered_map<string, shared_ptr<Item> > >&,
            unordered_map<string, unordered_map<string, double> >&,
            unordered_map<string, unordered_map<string, double> >&,
            unordered_map<string, shared_ptr<Json::Value> >&,
            unordered_map<string, vector<string> >&,
            unordered_map<string, double>&,
            const string&, const string&);

    };
}

#endif
