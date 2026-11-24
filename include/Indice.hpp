#ifndef INDICE_HPP
#define INDICE_HPP

#include "Lista.hpp"

struct Par { int id_objeto; int valor; };

inline bool operator==(const Par& a, const Par& b) {
    return a.id_objeto == b.id_objeto && a.valor == b.valor;
}

inline std::ostream& operator<<(std::ostream& os, const Par& p) {
    os << "[" << p.id_objeto << "] " << p.valor; 
    return os;
}

// Iremos usar id_objeto = id_cliente e valor = poder

class Indice {
    public:
        virtual ~Indice() {}

        // Retorna a quantidade de itens salvos
        virtual int Get_Tamanho() const = 0;

        // Retorna os dados para a analise
        virtual Analise Get_Analise() const = 0;
        virtual void Zerar_Analise() = 0;

        virtual void Inserir(int poder, int id_cliente) = 0;
        virtual void Remover(int poder, int id_cliente) = 0;

        // ids com essa poder, em ordem crescente de id
        virtual void Buscar(int id_cliente, Lista<int>& resultado) const = 0;

        // Retorna ppares em [min, max], ordenados por (pode, id_cliente)
        virtual void Faixa(int min, int max, Lista<Par>& resultado) const = 0;

        // Retorna todos os atributos em uma lista
        virtual void Todos(Lista<Par>& resultado) const = 0;
        virtual void Converter_Indice(Indice& i) = 0;

    protected:
        // Variável para análise experimental
        mutable Analise ana;

        void QuickSort(Lista<int>& lista) const;
        void QuickSort(Lista<Par>& lista) const;
};

#include "ListaEncadeada.hpp"
class TabelaHash : public Indice {
    public:
        TabelaHash(int capacidade_inicial = 17);
        ~TabelaHash();
                
        int Get_Tamanho() const override;
        // Variáveis de análise
        Analise Get_Analise() const override; void Zerar_Analise() override;

        void Inserir(int pode, int id_cliente) override;
        void Remover(int pode, int id_cliente) override;
        
        void Buscar(int pode, Lista<int>& resultado) const override;
        void Faixa(int min, int max, Lista<Par>& resultado) const override;

        void Todos(Lista<Par>& resultado) const override;
        void Converter_Indice(Indice& i) override;

    private:
        // Assim evitamos cópias acidentais!
        TabelaHash(const TabelaHash&) = delete;
        TabelaHash& operator=(const TabelaHash&) = delete;

        int tamanho;
        int M; // quantos "baldes" teremos
        ListaEncadeada<Par>* Tabela;

        int Hash(int chave) const;
        void ReHash();
};

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

// Para a ordenação da árvore, primeiro comparamos o poder e depois o id do cliente
class ArvoreAVL : public Indice {
    public:
        ArvoreAVL(); ~ArvoreAVL();

        int Get_Tamanho() const override;
        int Get_Altura() const;
        // Variáveis de análise
        Analise Get_Analise() const override; void Zerar_Analise() override;
        
        void Inserir(int pode, int id_cliente) override;
        void Remover(int pode, int id_cliente) override;

        void Buscar(int pode, Lista<int>& resultado) const override;
        void Faixa(int min, int max, Lista<Par>& resultado) const override;

        void Todos(Lista<Par>& resultado) const override;
        void Converter_Indice(Indice& i) override;

    private:
        // Assim evitamos cópias acidentais!
        ArvoreAVL(const ArvoreAVL&) = delete;
        ArvoreAVL& operator=(const ArvoreAVL&) = delete;

        int tamanho;
        TipoNo* raiz;

        void InsereRecursivo(TipoNo* &p, Par par);
        void RemoveRecursivo(TipoNo* &p, Par par);

        void LiberaRecursivo(TipoNo* p);
        void BuscaRecursivo(TipoNo* p, int pode, Lista<int>& resultado) const;
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