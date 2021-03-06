#ifndef PREDITOR_H
#define PREDITOR_H

#include "../../Estruturas/Item/Item.h"

#include <unordered_map>
#include <json/json.h>
#include <memory>
#include <vector>

using namespace Estruturas;
using namespace std;

namespace Algoritmos {
    struct Preditor {
        static double calcularPredicaoAPartirVetorMedioUsuario(
            unordered_map<string, unordered_map<string, double> >&,
            unordered_map<string, unordered_map<string, double> >&,
            vector<string>&,
            const string&, const string&);

        static double predizer(
            unordered_map<string, unordered_map<string, shared_ptr<Item> > >&,
            unordered_map<string, unordered_map<string, double> >&,
            unordered_map<string, unordered_map<string, double> >&,
            unordered_map<string, shared_ptr<Json::Value> >&,
            unordered_map<string, vector<string> >&,
            unordered_map<string, double>&,
            const string&, const string&);
    };
};

#endif
