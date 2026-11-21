#ifndef MAPA_HPP
#define MAPA_HPP

#include <string>
#include "./include/Lista.hpp"
typedef struct No {
    int destino; // o vizinho
    int peso; // peso da aresta
} No;

class Mapa {
    public:
        Mapa();

        // Cadastro
        int Adicionar_Regiao(const std::string& nome);   // retorna o id
        void Adicionar_Rota(int u, int v, int custo);     // mão dupla: insere nas duas listas

        // Consultas
        const std::string& Nome_Regiao(int id) const;
        int Num_Regioes() const;
        int Num_Rotas() const;
        bool Existe_Rota(int u, int v) const;             // opcional (testes)

        // Conectividade por busca (alternativa ao union-find)
        bool Conectados_Busca(int origem, int destino);

        // Instrumentação
        int Regioes_Visitadas_Ultima() const;
        long long Regioes_Visitadas_Total() const;

    private:
        Lista<std::string> nomes;
        Lista<Lista<No>> listas;
        int num_rotas;

        // Buffers reaproveitados entre buscas (sem alocar dentro do laço medido)
        Lista<int> marca;     // marca[v] == rodada  <=>  v visitado
        Lista<int> fila;      // fila da BFS: índice de leitura + push, sem remoção
        int rodada;

        int visitadas_ultima;
        long long visitadas_total;
};

#endif