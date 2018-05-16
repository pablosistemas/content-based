#include "TfIdf.h"

#include <strings.h>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

namespace Algoritmos {
    double TfIdf::tf (const vector<std::string>& doc, const std::string& termo) {
        double tf = 0;
        for (auto palavra = doc.begin(); palavra != doc.end(); palavra++) {
            if (strcasecmp(palavra->c_str(), termo.c_str()) == 0) {
                tf++;
            }
        }
        return tf/doc.size();
    }

    double TfIdf::idf(const std::unordered_map<std::string, std::vector<std::string> >& docs, const string& termo) {
        double n = 0;
        for (auto doc = docs.begin(); doc != docs.end(); doc++) {
            for (auto palavra = doc->second.begin(); palavra != doc->second.end(); palavra++) {
                if (strcasecmp(palavra->c_str(), termo.c_str()) == 0) {
                    n++;
                    break;
                }
            }
        }
        return log(docs.size() / n);
    }
}
