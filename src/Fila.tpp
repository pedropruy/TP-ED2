#include <iostream>

template<typename TipoItem>
TipoCelula<TipoItem>::TipoCelula() { prox = nullptr; }

template<typename TipoItem>
Fila<TipoItem>::Fila() {
    frente = new TipoCelula<TipoItem>();
    tras = frente;
    tamanho = 0;
}

template<typename TipoItem>
Fila<TipoItem>::~Fila() { Limpa(); delete frente; }

template<typename TipoItem>
int Fila<TipoItem>::Get_Tamanho() const { return tamanho; }

template<typename TipoItem>
void Fila<TipoItem>::Enfileira(const TipoItem& item) {
    TipoCelula<TipoItem>* nova;
    nova = new TipoCelula<TipoItem>();
    CONTA(ana, alocacoes, 1);
    nova->item = item;
    tras->prox = nova;
    tras = nova;
    tamanho++;
}

template<typename TipoItem>
TipoItem Fila<TipoItem>::Desenfileira() {
    if (tamanho == 0) throw "Fila está vazia!";

    TipoCelula<TipoItem>* aux;
    TipoItem item;
    item = frente->prox->item;
    aux = frente;
    frente = frente->prox;
    delete aux;
    CONTA(ana, liberacoes, 1);
    tamanho--;
    return item;
}

template<typename TipoItem>
void Fila<TipoItem>::Imprime(){
    if (tamanho == 0) return;
    TipoCelula<TipoItem>* aux = this->frente->prox;
    while (aux != nullptr) {
        std::cout << aux->item << std::endl;
        aux = aux->prox;
    }
}

template<typename TipoItem>
void Fila<TipoItem>::Limpa(){
    TipoCelula<TipoItem>* aux;
    aux = frente->prox;
    while (aux != nullptr) {
        frente->prox = aux->prox;
        delete aux;
        CONTA(ana, liberacoes, 1);
        aux = frente->prox;
    }
    tamanho = 0;
    tras = frente;
}

template<typename TipoItem>
Analise Fila<TipoItem>::Get_Analise() const { return ana; }

template<typename TipoItem>
void Fila<TipoItem>::Zerar_Analise() { ana.Zerar(); }

template<typename TipoItem>
long long Fila<TipoItem>::Bytes_Usados() const {
    return (long long)(tamanho + 1) * sizeof(TipoCelula<TipoItem>); // +1: sentinela
}