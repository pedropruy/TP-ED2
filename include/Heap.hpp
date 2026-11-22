#ifndef HEAP_HPP
#define HEAP_HPP

#include "Lista.hpp"

struct Filiado { int id_cliente; int prioridade; };
// Redefinição para facilitar a leitura do código
bool inline operator< (const Filiado& a, const Filiado& b) {
    if (a.prioridade != b.prioridade)
        return a.prioridade < b.prioridade;
    return a.id_cliente > b.id_cliente;
}

bool inline operator> (const Filiado& a, const Filiado& b) {
    if (a.prioridade != b.prioridade)
        return a.prioridade > b.prioridade;
    return a.id_cliente < b.id_cliente;
}

class Heap {
    public:
        int Get_Tamanho() const;
        void Insere(int id_cliente, int prioridade);
        void Insere(Filiado cliente);
        Filiado Remove(); // tira o maior
        Filiado Maximo(); // apenas vê quem é o maior
        bool Vazio() const;
    private:
        int GetAncestral(int i);
        int GetSucessorEsq(int i);
        int GetSucessorDir(int i);
        void Sobe(int i);
        void Desce(int i);
        Lista<Filiado> fila;
};

#endif