#include "../include/DSU.hpp"

void DSU::Make(int x) {
    pai.Insere_Final(x);
    rank.Insere_Final(0);
}

int DSU::Find(int x){
    if(pai[x] != x)
        pai[x]= Find(pai[x]);
    return pai[x];
}

void DSU::Union(int x, int y){
    int raiz_x = Find(x);
    int raiz_y = Find(y);
    if(raiz_x == raiz_y) return;
    if(rank[raiz_x] < rank[raiz_y])
        pai[raiz_x] = raiz_y;
    else if(rank[raiz_x] > rank[raiz_y])
        pai[raiz_y] = raiz_x;
    else {
        pai[raiz_x] = raiz_y;
        rank[raiz_y]++;
    }
}