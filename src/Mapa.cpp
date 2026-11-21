#include "../include/Mapa.hpp"

bool Mapa::Existe(int u, int v) {
    No* p = listas[u];
    while (p != nullptr && p->destino != v)
        p = p->prox;
    return p != nullptr;
}