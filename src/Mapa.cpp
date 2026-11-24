#include "../include/Mapa.hpp"

Mapa::Mapa() { num_rotas = 0; }

const std::string& Mapa::Get_Nome_Regiao(int id) const { return nomes[id]; }
int Mapa::Get_Num_Regioes() const { return listas.Get_Tamanho(); }
int Mapa::Get_Num_Rotas() const { return num_rotas; }

Analise Mapa::Get_Analise() const {
    Analise aux = ana;
    Analise a_nomes = nomes.Get_Analise();
    Analise a_listas = listas.Get_Analise();
    Analise a_marca = marca.Get_Analise();

    aux.alocacoes += a_nomes.alocacoes + a_listas.alocacoes + a_marca.alocacoes;
    aux.liberacoes += a_nomes.liberacoes + a_listas.liberacoes + a_marca.liberacoes;

    long long bytes_adj = 0;
    for (int i = 0; i < listas.Get_Tamanho(); i++) {
        Analise a_adj = listas[i].Get_Analise();
        aux.alocacoes += a_adj.alocacoes;
        aux.liberacoes += a_adj.liberacoes;
        bytes_adj += a_adj.bytes_memoria;
    }

    aux.bytes_memoria = sizeof(Mapa) + a_nomes.bytes_memoria + a_listas.bytes_memoria + a_marca.bytes_memoria + bytes_adj;
    return aux;
}

void Mapa::Zerar_Analise() {
    ana.Zerar();
    nomes.Zerar_Analise();
    listas.Zerar_Analise();
    marca.Zerar_Analise();
    for (int i = 0; i < listas.Get_Tamanho(); i++)
        listas[i].Zerar_Analise();
}

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
    bool achou = Busca_Em_Profundidade(origem, destino);

    // Define falso em todos os vertices
    for(int i = 0; i < marca.Get_Tamanho(); i++)
        marca[i] = false;
    return achou;
}

bool Mapa::Busca_Em_Profundidade(int atual, int destino) {
    // Passamos pelo ponto atual
    marca[atual] = true;
    CONTA(ana, regioes_visitadas, 1);

    if (atual == destino) return true;

    const Lista<No>& vizinhos = listas[atual];
    for (int i = 0; i < vizinhos.Get_Tamanho(); i++) {
        int vizinho = vizinhos[i].destino;
        CONTA(ana, comparacoes, 1);
        if (!marca[vizinho])
            if (Busca_Em_Profundidade(vizinho, destino)) return true;
    }
    return false;
}