#include "Estatistica.h"

#include <random>
#include <cmath>

namespace Algoritmos {
    double Estatistica::retornarAmostraDistribuicaoDados(double shape, double scale) {
        default_random_engine gen;
        weibull_distribution<double> dist(shape, scale);
        return dist(gen);
    }
}