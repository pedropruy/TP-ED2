#ifndef TABELAHASH_HPP
#define TABELAHASH_HPP

#include "Indice.hpp"
#include "ListaEncadeada.hpp"

class TabelaHash : public Indice {
    public:
        TabelaHash(int capacidade_inicial = 17);
        ~TabelaHash();
                
        int Get_Tamanho() const override;
        void Inserir(int chave, int valor) override;
        void Remover(int chave, int valor) override;
        
        void Buscar(int chave, Lista<int>& resultado) const override;
        void Faixa(int min, int max, Lista<Par>& resultado) const override;

        void Todos(Lista<Par>& resultado) const override;
    private:
        // Assim evitamos cópias acidentais!
        TabelaHash(const TabelaHash&) = delete;
        TabelaHash& operator=(const TabelaHash&) = delete;

        int tamanho;
        int M; // quantos "baldes" teremos
        ListaEncadeada<Par>* Tabela;

        void QuickSort(Lista<int>& lista) const;

        int Hash(int chave) const;
};

#endif