#include "../include/TabelaHash.hpp"


TabelaHash::TabelaHash(int capacidade_inicial) : tamanho(0), M(capacidade_inicial) {
    Tabela = new ListaEncadeada<Par>[M];
}

TabelaHash::~TabelaHash() { delete[] Tabela; }
                
int TabelaHash::Get_Tamanho() const { return tamanho; }

void TabelaHash::Inserir(int chave, int valor) {
    int ind = Hash(chave); // divisão devolve posição
    Par p = {chave, valor};
    Tabela[ind].Insere_Final(p);
    tamanho++;
}

void TabelaHash::Remover(int chave, int valor) {
    Par p = {chave, valor};
    int ind = Hash(chave);
    Tabela[ind].Remove_Item(p);
    tamanho--;
}
        
void TabelaHash::Buscar(int chave, Lista<int>& resultado) const {
    resultado.Limpa();

    const ListaEncadeada<Par>& lista = Tabela[Hash(chave)];
    if (lista.Get_Tamanho() == 0) return;
    TipoCelula<Par> *p = lista.primeiro->Get_Prox();
    
    while (p != nullptr) {
        Par par = p->Get_Item();
        if (par.poder == chave)
            resultado.Insere_Final(par.id_cliente);
        p = p->Get_Prox();
    }

    QuickSort(resultado);
}

// Como hash não tem ordem, teremos que varrer todos os índices
void TabelaHash::Faixa(int min, int max, Lista<Par>& resultado) const {
    resultado.Limpa();

    for (int i = 0; i < M; i++) {
        const ListaEncadeada<Par>& lista = Tabela[i];
        if (lista.Get_Tamanho() == 0) continue;

        TipoCelula<Par> *p = lista.primeiro->Get_Prox();
        while (p != nullptr) {
            Par par = p->Get_Item();
            if (par.poder >= min && par.poder <= max)
                resultado.Insere_Final(par);
            p = p->Get_Prox();
        }
    }

}

void TabelaHash::Todos(Lista<Par>& resultado) const {
    resultado.Limpa();

    for (int i = 0; i < M; i++) {
        const ListaEncadeada<Par>& lista = Tabela[i];
        if (lista.Get_Tamanho() == 0) continue;

        TipoCelula<Par> *p = lista.primeiro->Get_Prox();
        while (p != nullptr) {
            resultado.Insere_Final(p->Get_Item());
            p = p->Get_Prox();
        }
    }
}

int TabelaHash::Hash(int chave) const {
    int h = chave % M;
    return (h < 0) ? h + M : h; // correção caso for negativo
}

int Particao_Lomuto(Lista<int>& lista, int p, int r) {
    // Iremos escolher o pivô sempre ao meio
    int pos_pivo = p + (r - p) / 2;
    // Troca de lugar o pivô meio com o do fim
    CONTA(ana_ord, movimentos_ord, 2); // troca pivô com o último
    int temp_pivo = lista.Get_Item(pos_pivo);
    int temp_fim = lista.Get_Item(r);
    lista.Set_Item(temp_fim, pos_pivo);
    lista.Set_Item(temp_pivo, r);

    int X = lista.Get_Item(r); // pivô: número do meio    
    int i = p - 1;
        for (int j = p; j < r; j++) {
        int Y = lista.Get_Item(j);

        // Comparamos apenas com o ID(int)
        CONTA(ana_ord, comparacoes_ord, 1);
        if (Y < X) {
            i++;
            CONTA(ana_ord, movimentos_ord, 2); // troca
            int w = lista.Get_Item(i);
            lista.Set_Item(Y, i);
            lista.Set_Item(w, j);
        }
    }
    
    // colocando w na posição de pivô
    CONTA(ana_ord, movimentos_ord, 2); // coloca o pivô na posição final
    int w = lista.Get_Item(i + 1);
    lista.Set_Item(lista.Get_Item(r), i + 1);
    lista.Set_Item(w, r);
    
    return i + 1; // retornando a posição do pivô
}

void Ordena(int Esq, int Dir, Lista<int>& lista) {
    if (Esq < Dir) {
        int q = Particao_Lomuto(lista, Esq, Dir);
        // Como estamos usando Partição de Lomuto, q já está na posição correta
        Ordena(Esq, q - 1, lista);
        Ordena(q + 1, Dir, lista);
    }
}

void TabelaHash::QuickSort(Lista<int>& lista) const { 
    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista); 
}