#include "../Estatistica/Estatistica.h"
#include "../Cosseno/Cosseno.h"
#include "Similaridade.h"

#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

namespace Algoritmos {
    double Similaridade::calcularSimilaridadeItemAtualItensHistoricosUsuario(
        unordered_map<string, unordered_map<string, shared_ptr<Item> > >&historicoUsuario,
        unordered_map<string, unordered_map<string, double> >& indiceInvertidoTfDocumentosPalavras,
        unordered_map<string, unordered_map<string, double> >& similaridades,
        unordered_map<string, shared_ptr<Json::Value> >& biblioteca,
        unordered_map<string, vector<string> >& palavrasChaveDocumentos,
        unordered_map<string, double>& indiceIdfPalavras,
        const string& itemId, const string& usuarioId) {
        if (biblioteca.count(itemId) == 0) {
            return Estatistica::retornarAmostraDistribuicaoDados(4.659206, 7.962903);
        }
        double num = 0;
        double den = 0;
        for(auto it = historicoUsuario[usuarioId].begin(); it != historicoUsuario[usuarioId].end(); it++) {
            if (similaridades[itemId].count(it->first) == 0) {
                auto similaridadeCosseno = Cosseno::calcularSimilaridade(
                    indiceInvertidoTfDocumentosPalavras,
                    palavrasChaveDocumentos,
                    indiceIdfPalavras,
                    itemId,
                    it->first);

                // auto similaridadeDice = Dice::calcularCoeficiente(biblioteca[itemId], biblioteca[it->first]);
                // auto similaridade = (similaridadeCosseno + similaridadeDice) / 2.0;
                auto similaridade = similaridadeCosseno;
                similaridades[itemId][it->first] = similaridades[itemId][it->first] = similaridade;
            }

            num += similaridades[itemId][it->first] * it->second.get()->avaliacao;
            den += similaridades[itemId][it->first];
        }
        if ((int)abs(den) == 0) { 
            return Estatistica::retornarAmostraDistribuicaoDados(4.659206, 7.962903);
        }
        return num/den;
    }

}