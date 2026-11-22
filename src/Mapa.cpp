#include "../include/Mapa.hpp"

Mapa::Mapa() {
    num_rotas = 0;
    rodada = 0;
    visitadas_ultima = 0;
    visitadas_total = 0;
}

const std::string& Mapa::Get_Nome_Regiao(int id) const { return nomes[id]; }
int Mapa::Get_Num_Regioes() const { return listas.Get_Tamanho(); }
int Mapa::Get_Num_Rotas() const { return num_rotas; }

int Mapa::Adicionar_Regiao(const std::string& nome) {
    nomes.Insere_Final(nome);
    Lista<No> rotas;
    listas.Insere_Final(rotas);
    marca.Insere_Final(0); // nasce não visitada (rodada começa em 1)
    return listas.Get_Tamanho()-1;
}
void Mapa::Adicionar_Rota(int u, int v, int custo) {
    listas[u].Insere_Final({v, custo});
    listas[v].Insere_Final({u, custo});
    num_rotas++;
}

// BFS com early exit. Em vez de zerar um vetor de visitados a cada consulta (O(V)),
// usamos a "rodada": v foi visitado nesta busca <=> marca[v] == rodada.
bool Mapa::Conectados_Busca(int origem, int destino) {
    visitadas_ultima = 0;
    rodada++;
    fila.Limpa();

    // Uma região sempre alcança a si mesma (mesma resposta do union-find)
    marca[origem] = rodada;
    visitadas_ultima++;
    fila.Insere_Final(origem);
    bool achou = (origem == destino);

    int ini = 0; // índice de leitura da fila (sem remover elementos)
    while (!achou && ini < fila.Get_Tamanho()) {
        int u = fila[ini++];
        const Lista<No>& vizinhos = listas[u];

        for (int i = 0; i < vizinhos.Get_Tamanho(); i++) {
            int v = vizinhos[i].destino;
            if (marca[v] == rodada) continue; // já visitada

            marca[v] = rodada;
            visitadas_ultima++;
            if (v == destino) { achou = true; break; }
            fila.Insere_Final(v);
        }
    }

    visitadas_total += visitadas_ultima;
    return achou;
}

int Mapa::Regioes_Visitadas_Ultima() const { return visitadas_ultima; }
long long Mapa::Regioes_Visitadas_Total() const { return visitadas_total; }