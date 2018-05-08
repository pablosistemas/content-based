#include "TfIdf.h"

#include <strings.h>
#include <vector>
#include <cmath>

using namespace std;

namespace Algoritmos {
    double TfIdf::tf (const vector<string>& doc, const string& termo) {
        double tf = 0;
        for (auto &&palavra : doc) {
            if (strcasecmp(palavra.c_str(), termo.c_str()) == 0) {
                tf++;
            }
        }
        return tf/doc.size();
    }

    double TfIdf::idf(const vector<vector<string>>& docs, const string& termo) {
        double n = 0;
        for (vector<string> doc : docs) {
            for (string word : doc) {
                if (strcasecmp(palavra.c_str(), termo.c_str()) == 0) {
                    n++;
                    break;
                }
            }
        }
        return log(docs.size() / n);
    }

    double TfIdf::tfIdf(const vector<string>& doc, const vector<vector<string>>& docs, const string& termo) {
        return tf(doc, term) * idf(docs, term);
    }
}
