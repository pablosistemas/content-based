#include <algorithm>
#include <vector>

#include "./Levenshtein.h"

namespace Algoritmos {
    int Levenshtein::distance(const std::string& s1, const std::string& s2) {
        const std::size_t len1 = s1.size(), len2 = s2.size();
        std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

        d[0][0] = 0;
        for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
        for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

        for(unsigned int i = 1; i <= len1; ++i)
            for(unsigned int j = 1; j <= len2; ++j)
                        // note that std::min({arg1, arg2, arg3}) works only in C++11,
                        // for C++98 use std::min(std::min(arg1, arg2), arg3)
                        d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
        return d[len1][len2];
    }
}
