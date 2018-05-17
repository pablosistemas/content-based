#include "../../Algoritmos/Similaridade/Similaridade.h"
#include "../Estatistica/Estatistica.h"
#include "Preditor.h"

#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace Algoritmos {
    double Preditor::calcularPredicaoAPartirVetorMedioUsuario(
        unordered_map<string, unordered_map<string, double> >& indiceTfDocumentosPalavras,
        unordered_map<string, unordered_map<string, double> >& vetorMedioPorUsuario,
        vector<string>& listaPalavras,
        const string& itemId, const string& usuarioId) {
        double num = 0.0;
        double den1, den2;
        den1 = den2 = 0.0;
        for(auto it = listaPalavras.begin(); it != listaPalavras.end(); it++) {
            double sim1 = vetorMedioPorUsuario[usuarioId][*it];
            double sim2 = indiceTfDocumentosPalavras[itemId][*it];
            if (vetorMedioPorUsuario[usuarioId].count(*it) > 0 && indiceTfDocumentosPalavras[itemId].count(*it) > 0) {
                num += sim1 * sim2;
            }
            den1 += sim1 * sim1;
            den2 += sim2 * sim2;
        }
        if (den1 == 0.0 || den2 == 0.0) {
            return Estatistica::retornarAmostraDistribuicaoDados(4.659206, 7.962903);
        }
        return num/(sqrt(den1) * sqrt(den2));
    }

    double Preditor::predizer(
        unordered_map<string, unordered_map<string, shared_ptr<Item> > >&historicoUsuario,
        unordered_map<string, unordered_map<string, double> >& indiceInvertidoTfDocumentosPalavras,
        unordered_map<string, unordered_map<string, double> >& similaridades,
        unordered_map<string, shared_ptr<Json::Value> >& biblioteca,
        unordered_map<string, vector<string> >& palavrasChaveDocumentos,
        unordered_map<string, double>& indiceIdfPalavras,
        const string& usuarioId, const string& itemId) {
        return Similaridade::calcularSimilaridadeItemAtualItensHistoricosUsuario(
            historicoUsuario,
            indiceInvertidoTfDocumentosPalavras,
            similaridades,
            biblioteca,
            palavrasChaveDocumentos,
            indiceIdfPalavras,
            itemId, usuarioId);
        // return calcularPredicaoAPartirVetorMedioUsuario(itemId, usuarioId);
    }
}
