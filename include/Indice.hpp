#ifndef INDICE_HPP
#define INDICE_HPP

#include "Lista.hpp"

struct Par { int id_cliente; int poder; };

inline bool operator==(const Par& a, const Par& b) {
    return a.id_cliente == b.id_cliente && a.poder == b.poder;
}

// chave = poder | valor = id_cliente
class Indice {
public:
    virtual ~Indice() {}

    virtual int Get_Tamanho() const = 0;

    virtual void Inserir(int chave, int valor) = 0;
    virtual void Remover(int chave, int valor) = 0;

    // ids com essa chave, em ordem crescente de id
    virtual void Buscar(int valor, Lista<int>& resultado) const = 0;

    // pares em [min, max], ordenados por (chave, valor)
    virtual void Faixa(int min, int max, Lista<Par>& resultado) const = 0;

    // todos os pares (usado na migração)
    virtual void Todos(Lista<Par>& resultado) const = 0;

    virtual int Tamanho() const = 0;
};
#endif