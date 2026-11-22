#include "../include/Indice.hpp"

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

int Particao_Lomuto(Lista<Par>& lista, int p, int r) {
    // Iremos escolher o pivô sempre ao meio
    int pos_pivo = p + (r - p) / 2;
    // Troca de lugar o pivô meio com o do fim
    CONTA(ana_ord, movimentos_ord, 2); // troca pivô com o último
    Par temp_pivo = lista.Get_Item(pos_pivo);
    Par temp_fim = lista.Get_Item(r);
    lista.Set_Item(temp_fim, pos_pivo);
    lista.Set_Item(temp_pivo, r);

    Par X = lista.Get_Item(r); // pivô: número do meio
    int i = p - 1;    
    for (int j = p; j < r; j++) {
        Par J = lista.Get_Item(j);
        // Valor ser maior OU Se for o mesmo valor -> id é menor
        CONTA(ana_ord, comparacoes_ord, 1);
        if (J.valor < X.valor ||
           (J.valor == X.valor && J.id_objeto < X.id_objeto)) {
            i++;
            CONTA(ana_ord, movimentos_ord, 2); // troca
            // invertendo o lugar de item_j com item_w
            Par W = lista.Get_Item(i);
            lista.Set_Item(J, i);
            lista.Set_Item(W, j);
        }
    }
    
    // colocando w na posição de pivô
    CONTA(ana_ord, movimentos_ord, 2); // coloca o pivô na posição final
    Par W = lista.Get_Item(i + 1);
    lista.Set_Item(lista.Get_Item(r), i + 1);
    lista.Set_Item(W, r);
    
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

void Ordena(int Esq, int Dir, Lista<Par>& lista) {
    if (Esq < Dir) {
        int q = Particao_Lomuto(lista, Esq, Dir);
        // Como estamos usando Partição de Lomuto, q já está na posição correta
        Ordena(Esq, q - 1, lista);
        Ordena(q + 1, Dir, lista);
    }
}

void Indice::QuickSort(Lista<int>& lista) const { 
    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista); 
}

void Indice::QuickSort(Lista<Par>& lista) const {
    if (lista.Get_Tamanho() <= 1) return;
    Ordena(0, lista.Get_Tamanho() - 1, lista); 
}

TabelaHash::TabelaHash(int capacidade_inicial) : tamanho(0), M(capacidade_inicial) {
    Tabela = new ListaEncadeada<Par>[M];
}

TabelaHash::~TabelaHash() { delete[] Tabela; }
                
int TabelaHash::Get_Tamanho() const { return tamanho; }

void TabelaHash::Inserir(int poder, int id_cliente) {
    if (tamanho >= M) ReHash();

    int ind = Hash(poder); // divisão devolve posição
    Par p = {id_cliente, poder};
    Tabela[ind].Insere_Final(p);
    tamanho++;
}

void TabelaHash::Remover(int poder, int id_cliente) {
    Par p = {id_cliente, poder};
    int ind = Hash(poder);
    Tabela[ind].Remove_Item(p);
    tamanho--;
}
        
void TabelaHash::Buscar(int poder, Lista<int>& resultado) const {
    resultado.Limpa();

    const ListaEncadeada<Par>& lista = Tabela[Hash(poder)];
    if (lista.Get_Tamanho() == 0) return;
    TipoCelula<Par> *p = lista.primeiro->Get_Prox();
    
    while (p != nullptr) {
        Par par = p->Get_Item();
        if (par.valor == poder)
            resultado.Insere_Final(par.id_objeto);
        p = p->Get_Prox();
    }

    //QuickSort(resultado);
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
            if (par.valor >= min && par.valor <= max)
                resultado.Insere_Final(par);
            p = p->Get_Prox();
        }
    }

    QuickSort(resultado);
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

void TabelaHash::Converter_Indice(Indice& i) {
    ArvoreAVL* avl = dynamic_cast<ArvoreAVL*>(&i);
    if (avl == nullptr) throw "Classe Indice invalida!";
    
    Lista<Par> todos_pares;
    Todos(todos_pares);
    for(auto& par : todos_pares)
        avl->Inserir(par.valor, par.id_objeto);
}

int TabelaHash::Hash(int chave) const {
    int h = chave % M;
    return (h < 0) ? h + M : h; // correção caso for negativo
}

void TabelaHash::ReHash() {
    Lista<Par> todos_valores;
    this->Todos(todos_valores);

    this->M = (M*2) + 1; // Mantém o valor de M ímpar
    delete[] this->Tabela;
    this->Tabela = new ListaEncadeada<Par>[M];

    this->tamanho = 0;
    for(auto& par : todos_valores)
        this->Inserir(par.valor, par.id_objeto);
}