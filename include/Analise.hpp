#ifndef ANALISE_HPP
#define ANALISE_HPP

#include <iostream>

struct Analise {
    long long comparacoes = 0; // comparações de chave (poder / id_cliente)
    long long alocacoes = 0; // alocações dinâmicas
    long long liberacoes = 0; // liberações de memória
    long long bytes_memoria = 0; // uso estimado de memória

    // Métricas específicas da Árvore AVL
    long long rotacoes = 0; // número de rotações
    long long altura_arvore = 0; // altura atual ou acumulada para média

    // Métricas específicas da Tabela Hash
    long long colisoes = 0; // inserções em índices já ocupados / passos na lista
    long long rehashes = 0; // quantidade de redimensionamentos da tabela

    // Métricas de Conectividade (Mapa / DSU)
    long long regioes_visitadas = 0; // vértices visitados na busca ou passos no Find

    void Zerar() { *this = Analise(); }

    Analise& operator+=(const Analise& a) {
        comparacoes += a.comparacoes;
        alocacoes += a.alocacoes;
        liberacoes += a.liberacoes;
        bytes_memoria += a.bytes_memoria;
        rotacoes += a.rotacoes;
        altura_arvore += a.altura_arvore;
        colisoes += a.colisoes;
        rehashes += a.rehashes;
        regioes_visitadas += a.regioes_visitadas;
        return *this;
    }

    Analise& operator/=(const long long num) {
        if (num == 0) return *this;
        comparacoes /= num;
        alocacoes /= num;
        liberacoes /= num;
        bytes_memoria /= num;
        rotacoes /= num;
        altura_arvore /= num;
        colisoes /= num;
        rehashes /= num;
        regioes_visitadas /= num;
        return *this;
    }

    Analise operator-(const Analise& a) const {
        Analise r;
        r.comparacoes = comparacoes - a.comparacoes;
        r.alocacoes = alocacoes - a.alocacoes;
        r.liberacoes = liberacoes - a.liberacoes;
        r.bytes_memoria = bytes_memoria - a.bytes_memoria;
        r.rotacoes = rotacoes - a.rotacoes;
        r.altura_arvore = altura_arvore - a.altura_arvore;
        r.colisoes = colisoes - a.colisoes;
        r.rehashes = rehashes - a.rehashes;
        r.regioes_visitadas = regioes_visitadas - a.regioes_visitadas;
        return r;
    }

    friend std::ostream& operator<<(std::ostream& os, const Analise& a) {
        os << "Comparacoes:        " << a.comparacoes << "\n"
           << "Rotacoes (AVL):     " << a.rotacoes << "\n"
           << "Altura (AVL):       " << a.altura_arvore << "\n"
           << "Colisoes (Hash):    " << a.colisoes << "\n"
           << "Rehashes (Hash):    " << a.rehashes << "\n"
           << "Regioes visitadas:  " << a.regioes_visitadas << "\n"
           << "Alocacoes:          " << a.alocacoes << "\n"
           << "Liberacoes:         " << a.liberacoes << "\n"
           << "Memoria (bytes):    " << a.bytes_memoria;
        return os;
    }
};

#ifdef ANALISES
    #define CONTA(obj, campo, n) ((obj).campo += (n))
    #define CONTA_VAR(var, n) ((var) += (n))
    #define DEFINE_VAR(obj, campo, n) ((obj).campo = (n))
#else
    #define CONTA(obj, campo, n) ((void)0)
    #define CONTA_VAR(var, n) ((void)0)
    #define DEFINE_VAR(obj, campo, n) ((void)0)
#endif

#endif