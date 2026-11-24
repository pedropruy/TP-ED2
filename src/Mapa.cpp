#include "../include/Mapa.hpp"

Mapa::Mapa() {
    num_rotas = 0;
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
    marca.Insere_Final(false);
    return listas.Get_Tamanho()-1;
}
void Mapa::Adicionar_Rota(int u, int v, int custo) {
    listas[u].Insere_Final({v, custo});
    listas[v].Insere_Final({u, custo});
    num_rotas++;
}

bool Mapa::Conectados_Busca(int origem, int destino) {
    visitadas_ultima = 0;

    bool achou = Busca_Em_Profundidade(origem, destino);
    visitadas_total += visitadas_ultima;

    // Define falso em todos os vertices
    for(int i = 0; i < marca.Get_Tamanho(); i++)
        marca[i] = false;
    return achou;
}

bool Mapa::Busca_Em_Profundidade(int atual, int destino) {
    // Passamos pelo ponto atual
    marca[atual] = true;
    visitadas_ultima++;

    if (atual == destino) return true;

    const Lista<No>& vizinhos = listas[atual];
    for (int i = 0; i < vizinhos.Get_Tamanho(); i++) {
        int vizinho = vizinhos[i].destino;
        if (!marca[vizinho])
            if (Busca_Em_Profundidade(vizinho, destino)) return true;
    }
    return false;
}

int Mapa::Regioes_Visitadas_Ultima() const { return visitadas_ultima; }
long long Mapa::Regioes_Visitadas_Total() const { return visitadas_total; }