#ifndef FILA_HPP
#define FILA_HPP

#include "Analise.hpp"

template<typename TipoItem>
class TipoCelula {
    public:
        TipoCelula();

    private:
        TipoItem item;
        TipoCelula<TipoItem>* prox;
        friend class Fila<TipoItem>;
};

template<typename TipoItem>
class Fila {
    public:
        Fila(); ~Fila();
        int Get_Tamanho() const;
        void Enfileira(const TipoItem& item);
        TipoItem Desenfileira();
        void Imprime();
        void Limpa();

        Analise Get_Analise() const; void Zerar_Analise();
        long long Bytes_Usados() const;
    private:
        mutable Analise ana;
        int tamanho;
        TipoCelula<TipoItem>* frente;
        TipoCelula<TipoItem>* tras;
};

#include "../src/Fila.tpp"

#endif