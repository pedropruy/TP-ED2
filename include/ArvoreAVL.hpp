#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

#include "Indice.hpp"
#include "Lista.hpp"

class TipoNo {
    public:
        TipoNo();
        TipoNo(Par _item);
    private:
        Par item;
        TipoNo *esq;
        TipoNo *dir;
        int altura; // novo: folha=0
        friend class ArvoreAVL;
};

// Para a ordenação da arvore, primeiro compara o poder e depois o id do cliente
class ArvoreAVL : public Indice {
    public:
        ArvoreAVL(); ~ArvoreAVL();

        int Get_Tamanho() const override;
        int Altura() const;
        void Inserir(int chave, int valor) override;
        void Remover(int chave, int valor) override;

        void Buscar(int chave, Lista<int>& resultado) const override;
        void Faixa(int min, int max, Lista<Par>& resultado) const override;

        void Todos(Lista<Par>& resultado) const override;

    private:
        // Assim evitamos cópias acidentais!
        ArvoreAVL(const ArvoreAVL&) = delete;
        ArvoreAVL& operator=(const ArvoreAVL&) = delete;

        int tamanho;
        TipoNo* raiz;

        void InsereRecursivo(TipoNo* &p, Par par);
        void RemoveRecursivo(TipoNo* &p, Par par);

        void LiberaRecursivo(TipoNo* p);
        void BuscaRecursivo(TipoNo* p, int chave, Lista<int>& resultado) const;
        void FaixaRecursivo(TipoNo* p, int min, int max, Lista<Par>& resultado) const;
        void TodosRecursivo(TipoNo* p, Lista<Par>& resultado) const;

        int Altura(TipoNo* p) const;
        int FB(TipoNo* p) const;
        void AtualizaAltura(TipoNo* p);
        void RotacaoDireita(TipoNo* &p);
        void RotacaoEsquerda(TipoNo* &p);
        void Balanceia(TipoNo* &p);
};

#endif