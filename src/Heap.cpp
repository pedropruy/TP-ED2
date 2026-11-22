#include "../include/Heap.hpp"

Heap::Heap() {}
Heap::~Heap() {}

int Heap::Get_Tamanho() const { return fila.Get_Tamanho(); }

void Heap::Insere(Filiado cliente) {
    fila.Insere_Final(cliente); // 1. nova folha no fim
    Sobe(fila.Get_Tamanho()-1); // 2. sobe
}

void Heap::Insere(int id_cliente, int prioridade) {
    Insere({id_cliente, prioridade});
}

void Heap::Sobe(int i) {
    int p = GetAncestral(i);
    while (i > 0 && (fila[i] > fila[p])) {
        Filiado aux = fila[i]; fila[i] = fila[p]; fila[p] = aux; // swap
        i = p;
        p = GetAncestral(i);
    }
}

Filiado Heap::Remove() {
    if (fila.Get_Tamanho() == 0) throw "Heap vazio";
    Filiado x = fila[0]; // 1. guarda o maior
    fila[0] = fila[fila.Get_Tamanho()-1]; // 2. último vai da raiz
    fila.Remove_Final(); // (Oficialmente retira o último da raiz)
    if (!Vazio()) Desce(0); // 3. desce
    return x;
}

void Heap::Desce(int i) {
    while (true) {
        int e = GetSucessorEsq(i);
        int d = GetSucessorDir(i);
        int maior = i;
        if (e < fila.Get_Tamanho() && fila[e] > fila[maior]) maior = e;
        if (d < fila.Get_Tamanho() && fila[d] > fila[maior]) maior = d;
        if (maior == i) return; // ja esta no lugar
        Filiado aux = fila[i]; fila[i] = fila[maior]; fila[maior] = aux; // swap
        i = maior;
    }
}

Filiado Heap::Maximo() { if (!Vazio()) return fila[0]; else return {-1,-1}; }
bool Heap::Vazio() const { return fila.Get_Tamanho() == 0; }
int Heap::GetAncestral(int i) { return (i-1)/2; }
int Heap::GetSucessorEsq(int i) { return 2*i + 1; }
int Heap::GetSucessorDir(int i) { return 2*i + 2; }