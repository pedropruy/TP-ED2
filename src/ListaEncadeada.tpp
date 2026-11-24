#include <iostream>

template<typename TipoItem>
TipoCelula<TipoItem>::TipoCelula() {
    prox = nullptr;
}

template<typename TipoItem>
TipoItem& TipoCelula<TipoItem>:: Get_Item() { return item; }

template<typename TipoItem>
TipoCelula<TipoItem>* TipoCelula<TipoItem>::Get_Prox() const { return prox; }

template<typename TipoItem>
ListaEncadeada<TipoItem>::ListaEncadeada() {
    tamanho = 0;
    primeiro = new TipoCelula<TipoItem>();
    ultimo = primeiro;
    CONTA(ana, alocacoes, 1);
}

template<typename TipoItem>
ListaEncadeada<TipoItem>::~ListaEncadeada() {
    Limpa();
    delete primeiro;
    CONTA(ana, liberacoes, 1);
}

// Construtor de cópia
template<typename TipoItem>
ListaEncadeada<TipoItem>::ListaEncadeada(const ListaEncadeada<TipoItem> &le) {
    tamanho = 0;
    primeiro = new TipoCelula<TipoItem>();
    ultimo = primeiro;

    TipoCelula<TipoItem>* p = le.primeiro->prox;
    while (p != nullptr) {
        Insere_Final(p->item);
        p = p->prox;
    }
}

// Operador de atribuição
template<typename TipoItem>
ListaEncadeada<TipoItem>& ListaEncadeada<TipoItem>::operator=(const ListaEncadeada<TipoItem> &le) {
    if (this != &le) {
        Limpa();
        TipoCelula<TipoItem>* p = le.primeiro->prox;
        while (p != nullptr) {
            Insere_Final(p->item);
            p = p->prox;
        }
    }
    return *this;
}

template<typename TipoItem>
int ListaEncadeada<TipoItem>::Get_Tamanho() const { 
    return tamanho; 
}

template<typename TipoItem>
TipoItem& ListaEncadeada<TipoItem>::Get_Item(int ind) {
    TipoCelula<TipoItem>* p;
    p = Posiciona(ind + 1);
    return p->item;
}

template<typename TipoItem>
TipoItem& ListaEncadeada<TipoItem>::Get_Item(int ind) const {
    TipoCelula<TipoItem>* p;
    p = Posiciona(ind + 1);
    return p->item;
}

template<typename TipoItem>
Analise ListaEncadeada<TipoItem>::Get_Analise() const {
    Analise aux = ana;
    // Sentinela + 'tamanho' células alocadas
    aux.bytes_memoria = sizeof(ListaEncadeada<TipoItem>) + ((tamanho + 1) * sizeof(TipoCelula<TipoItem>));
    return aux;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Zerar_Analise() {
    ana.Zerar();
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Set_Item(const TipoItem& item, int ind) {
    TipoCelula<TipoItem>* p;
    p = Posiciona(ind + 1);
    p->item = item;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Insere_Inicio(const TipoItem& item) {
    TipoCelula<TipoItem> *nova = new TipoCelula<TipoItem>();
    CONTA(ana, alocacoes, 1);
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;

    if (nova->prox == nullptr) ultimo = nova;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Insere_Final(const TipoItem& item) {
    TipoCelula<TipoItem> *nova = new TipoCelula<TipoItem>();
    CONTA(ana, alocacoes, 1);
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Insere_Posicao(const TipoItem& item, int pos) {
    TipoCelula<TipoItem> *p, *nova;
    p = Posiciona(pos, true);

    nova = new TipoCelula<TipoItem>();
    CONTA(ana, alocacoes, 1);
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;

    if (nova->prox == nullptr) ultimo = nova;
}

template<typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::Remove_Inicio() {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    TipoItem aux;
    TipoCelula<TipoItem> *p;

    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;
    if (primeiro->prox == nullptr)
        ultimo = primeiro;
    aux = p->item;
    delete p;
    CONTA(ana, liberacoes, 1);

    return aux;
}

template<typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::Remove_Final() {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    TipoItem aux;
    TipoCelula<TipoItem> *p;

    p = Posiciona(tamanho, true);

    p->prox = nullptr;
    tamanho--;
    aux = ultimo->item;
    delete ultimo;
    CONTA(ana, liberacoes, 1);
    ultimo = p;

    return aux;
}

template<typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::Remove_Posicao(int pos) {
    if (tamanho == 0) throw "ERRO: Lista vazia!";
    TipoItem aux;
    TipoCelula<TipoItem> *p, *q;

    p = Posiciona(pos, true);
    q = p->prox;
    p->prox = q->prox;
    tamanho--;
    aux = q->item;
    delete q;
    CONTA(ana, liberacoes, 1);
    if (p->prox == nullptr) ultimo = p;
    return aux;
}

template<typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::Remove_Item(const TipoItem& item) {
    TipoCelula<TipoItem> *p = primeiro, *q;
    while (p->prox != nullptr) {
        CONTA(ana, comparacoes, 1);
        if (p->prox->item == item) break;
        p = p->prox;
    }
    if (p->prox == nullptr) throw "ERRO: item nao esta presente";
    q = p->prox;
    p->prox = q->prox;
    TipoItem aux = q->item;
    delete q;
    CONTA(ana, liberacoes, 1);
    tamanho--;
    if (p->prox == nullptr) ultimo = p;
    return aux;
}

template<typename TipoItem>
TipoItem ListaEncadeada<TipoItem>::Pesquisa(const TipoItem& item, bool& achei) {
    TipoItem aux; achei = false;
    if (tamanho == 0) return aux;
    TipoCelula<TipoItem> *p = primeiro->prox;
    
    while (p != nullptr) {
        CONTA(ana, comparacoes, 1);
        if (p->item == item) {
            aux = p->item;
            achei = true;
            break;
        }
        p = p->prox;
    }
    return aux;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Imprime() {
    TipoCelula<TipoItem> *p = primeiro->prox;
    while (p != nullptr) {
        std::cout << p->item << std::endl; // pode ser que impressão esteja errado
        p = p->prox;
    }
    std::cout << std::endl;
}

template<typename TipoItem>
void ListaEncadeada<TipoItem>::Limpa() {
    TipoCelula<TipoItem> *p;
    p = primeiro->prox;
    while (p != nullptr) {
        primeiro->prox = p->prox;
        delete p;
        CONTA(ana, liberacoes, 1);
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

template<typename TipoItem>
TipoItem& ListaEncadeada<TipoItem>::operator[](int ind) {
    return Get_Item(ind);
}

template<typename TipoItem>
const TipoItem& ListaEncadeada<TipoItem>::operator[](int ind) const {
    return Get_Item(ind);
}

template<typename TipoItem>
TipoCelula<TipoItem>* ListaEncadeada<TipoItem>::Posiciona(int pos, bool antes) {
    if ((pos > tamanho) || (pos <= 0))
        throw "ERRO: Posicao Invalida!";
    TipoCelula<TipoItem> *p; 
    int i; 

    // posiciona na célula anterior à desejada
    p = primeiro;
    for (i = 1; i < pos; i++)
        p = p->prox;
    // vai para a próxima se antes for false
    if (!antes) p = p->prox;

    return p;
}

template<typename TipoItem>
TipoCelula<TipoItem>* ListaEncadeada<TipoItem>::Posiciona(int pos, bool antes) const {
    if ((pos > tamanho) || (pos <= 0))
        throw "ERRO: Posicao Invalida!";
    TipoCelula<TipoItem> *p; 
    int i; 

    // posiciona na célula anterior à desejada
    p = primeiro;
    for (i = 1; i < pos; i++)
        p = p->prox;
    // vai para a próxima se antes for false
    if (!antes) p = p->prox;

    return p;
}