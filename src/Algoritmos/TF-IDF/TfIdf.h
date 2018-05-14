#ifndef TFIDF_H
#define TFIDF_H

#include <vector>
#include <string>
#include <map>

using namespace std;

namespace Algoritmos {
    struct TfIdf {
        static double tfIdf(const vector<string>&, const vector<vector<string> >&, const string&);
        static double idf(const map<string, vector<string> >&, const string&);
        static double tf(const vector<string>&, const string&);
    };
}

#endif
