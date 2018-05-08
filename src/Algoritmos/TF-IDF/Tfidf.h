#ifdef TFIDF_H
#define TFIDF_H

#include <vector>

using namespace std;

namespace Algoritmos {
    struct TfIdf {
        double tf (const vector<string>&, const string&);
        double tfIdf(const vector<string>&, const vector<vector<string>>&, const string&);
        double tfIdf(const vector<string>&, const vector<vector<string>>&, const string&);
    };

}

#endif
