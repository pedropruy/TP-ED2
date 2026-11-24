#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include "Analise.hpp"

template<typename TipoItem> class ListaEncadeada;
class TabelaHash;

template<typename TipoItem>
class TipoCelula {
    public:
        TipoCelula();
        TipoItem& Get_Item();
        TipoCelula<TipoItem>* Get_Prox() const;
    private:
        TipoItem item;
        TipoCelula<TipoItem>* prox;
        friend class ListaEncadeada<TipoItem>;
};

template<typename TipoItem>
class ListaEncadeada {
    public:
        ListaEncadeada(); ~ListaEncadeada();
        ListaEncadeada(const ListaEncadeada &le);
        ListaEncadeada& operator= (const ListaEncadeada &le);

        int Get_Tamanho() const;
        TipoItem& Get_Item(int ind); TipoItem& Get_Item(int ind) const;
        void Set_Item(const TipoItem& item, int ind);

        // Variáveis de análise
        Analise Get_Analise() const; void Zerar_Analise();

        void Insere_Inicio(const TipoItem& item);
        void Insere_Final(const TipoItem& item);
        void Insere_Posicao(const TipoItem& item, int pos);

        TipoItem Remove_Inicio();
        TipoItem Remove_Final();
        TipoItem Remove_Posicao(int pos);
        TipoItem Remove_Item(const TipoItem& item);

        TipoItem Pesquisa(const TipoItem& item, bool& achei);
        void Imprime(); void Limpa();

        TipoItem& operator[](int ind);
        const TipoItem& operator[](int ind) const;
    private:
        mutable Analise ana;
        
        int tamanho;
        TipoCelula<TipoItem>* primeiro; // aponta para a cabeça
        TipoCelula<TipoItem>* ultimo; // aponta para a última
        TipoCelula<TipoItem>* Posiciona(int pos, bool antes = false);
        TipoCelula<TipoItem>* Posiciona(int pos, bool antes = false) const;
        friend class TabelaHash;
};

#include "../src/ListaEncadeada.tpp"

#endif