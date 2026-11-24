#ifndef MAPA_HPP
#define MAPA_HPP

#include "Lista.hpp"
#include <string>
typedef struct No {
    int destino; // o vizinho
    int peso; // peso da aresta
} No;

class Mapa {
    public:
        Mapa();
        const std::string& Get_Nome_Regiao(int id) const;
        int Get_Num_Regioes() const;
        int Get_Num_Rotas() const;

        // Variáveis de análise
        Analise Get_Analise() const; void Zerar_Analise();

        int Adicionar_Regiao(const std::string& nome); // retorna o id
        void Adicionar_Rota(int u, int v, int custo); // mão dupla: insere nas duas listas

        // Conectividade por busca (alternativa ao union-find)
        bool Conectados_Busca(int origem, int destino);
    private:
        mutable Analise ana;

        Lista<std::string> nomes;
        Lista<Lista<No>> listas;
        int num_rotas;

        Lista<bool> marca; // Usada para dizer se já passamos nesse ponto nessa busca
        bool Busca_Em_Profundidade(int atual, int destino);
};

#endif