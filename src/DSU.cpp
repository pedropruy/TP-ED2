#include "../include/DSU.hpp"

void DSU::Make(int x) {
    pai.Insere_Final(x);
    rank.Insere_Final(0);
}

int DSU::Find(int x){
    CONTA(ana, regioes_visitadas, 1);
    if (pai[x] != x)
        pai[x]= Find(pai[x]);
    return pai[x];
}

void DSU::Union(int x, int y) {
    int raiz_x = Find(x);
    int raiz_y = Find(y);
    CONTA(ana, comparacoes, 1);
    if (raiz_x == raiz_y) return;

    CONTA(ana, comparacoes, 1);
    if (rank[raiz_x] < rank[raiz_y])
        pai[raiz_x] = raiz_y;
    else if (rank[raiz_x] > rank[raiz_y])
        pai[raiz_y] = raiz_x;
    else {
        pai[raiz_x] = raiz_y;
        rank[raiz_y]++;
    }
}

Analise DSU::Get_Analise() const {
    Analise aux = ana;
    Analise a_pai = pai.Get_Analise();
    Analise a_rank = rank.Get_Analise();

    aux.alocacoes += a_pai.alocacoes + a_rank.alocacoes;
    aux.liberacoes += a_pai.liberacoes + a_rank.liberacoes;
    aux.bytes_memoria = sizeof(DSU) + a_pai.bytes_memoria + a_rank.bytes_memoria;
    return aux;
}

void DSU::Zerar_Analise() {
    ana.Zerar();
    pai.Zerar_Analise();
    rank.Zerar_Analise();
}