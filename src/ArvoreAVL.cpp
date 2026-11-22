#include "../include/Indice.hpp"

TipoNo::TipoNo() {
    item = {-1, 0};
    esq = nullptr;
    dir = nullptr;
    altura = 0; // nasce folha
}

TipoNo::TipoNo(Par _item) {
    item = _item;
    esq = nullptr;
    dir = nullptr;
    altura = 0; // nasce folha
}

ArvoreAVL::ArvoreAVL() {
    tamanho = 0;
    raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL() {
    LiberaRecursivo(raiz);
    raiz = nullptr;
    tamanho = 0;
}

void ArvoreAVL::LiberaRecursivo(TipoNo* p) {
    if (p == nullptr) return;
    LiberaRecursivo(p->esq);
    LiberaRecursivo(p->dir);
    delete p;
}

int ArvoreAVL::Get_Tamanho() const { return tamanho; }
int ArvoreAVL::Altura() const { return Altura(raiz); }

void ArvoreAVL::Inserir(int poder, int id_cliente) {
    Par p = {id_cliente, poder};
    InsereRecursivo(raiz, p);
}

void ArvoreAVL::InsereRecursivo(TipoNo* &p, Par item) {
    if (p == nullptr) {
        p = new TipoNo(item);
        tamanho++;
        return; // novo
    }

    if (item.valor < p->item.valor) InsereRecursivo(p->esq, item);
    else if (item.valor > p->item.valor) InsereRecursivo(p->dir, item);
    else {
        // Desempate pelo id_cliente
        if (item.id_objeto < p->item.id_objeto)
            InsereRecursivo(p->esq, item);
        else if (item.id_objeto > p->item.id_objeto)
            InsereRecursivo(p->dir, item);
        else return; // Par duplicado
    }
    Balanceia(p); // novo
}

void ArvoreAVL::Remover(int poder, int id_cliente) {
    Par p = {id_cliente, poder};
    RemoveRecursivo(raiz, p);
}

void ArvoreAVL::RemoveRecursivo(TipoNo* &p, Par item) {
    if (p == nullptr) return; // não achou

    if (item.valor < p->item.valor) RemoveRecursivo(p->esq, item);
    else if (item.valor > p->item.valor) RemoveRecursivo(p->dir, item);
    else {
        // Desempate pelo id_cliente
        if (item.id_objeto < p->item.id_objeto)
            RemoveRecursivo(p->esq, item);
        else if (item.id_objeto > p->item.id_objeto)
            RemoveRecursivo(p->dir, item);
        else {
            // Achou o nó exato a ser removido
            if (p->esq == nullptr || p->dir == nullptr) {
                TipoNo *aux = p; // 0 ou 1 filho
                p = (p->esq != nullptr) ? p->esq : p->dir;
                delete aux;  
                tamanho--;
            } else { // 2 filhos
                TipoNo *a = p->esq; // antecessor
                while (a->dir != nullptr) a = a->dir;
                p->item = a->item;
                RemoveRecursivo(p->esq, a->item);
            }
        }
    }

    if (p != nullptr) Balanceia(p); // na volta
}

int ArvoreAVL::Altura(TipoNo* p) const {
    if (p == nullptr) return -1; // vazia
    return p->altura;
}

void ArvoreAVL::Buscar(int poder, Lista<int>& resultado) const {
    resultado.Limpa();
    BuscaRecursivo(raiz, poder, resultado);
    //QuickSort(resultado);
}

void ArvoreAVL::BuscaRecursivo(TipoNo* p, int poder, Lista<int>& resultado) const {
    if (p == nullptr) return;

    if (poder < p->item.valor) {
        BuscaRecursivo(p->esq, poder, resultado);
    } else if (poder > p->item.valor) {
        BuscaRecursivo(p->dir, poder, resultado);
    } else {
        BuscaRecursivo(p->esq, poder, resultado);
        resultado.Insere_Final(p->item.id_objeto);
        BuscaRecursivo(p->dir, poder, resultado);
    }
}

void ArvoreAVL::Faixa(int min, int max, Lista<Par>& resultado) const {
    resultado.Limpa();
    FaixaRecursivo(raiz, min, max, resultado);
}

void ArvoreAVL::FaixaRecursivo(TipoNo* p, int min, int max, Lista<Par>& resultado) const {
    if (p == nullptr) return;

    // Para a esquerda caso encontrarmos um valor menor
    if (p->item.valor >= min)
        FaixaRecursivo(p->esq, min, max, resultado);

    if (p->item.valor >= min && p->item.valor <= max)
        resultado.Insere_Final(p->item);

    // Para a direita caso encontrarmos um valor maior
    if (p->item.valor <= max)
        FaixaRecursivo(p->dir, min, max, resultado);
    
}

void ArvoreAVL::Todos(Lista<Par>& resultado) const {
    resultado.Limpa();
    TodosRecursivo(raiz, resultado);
}

void ArvoreAVL::TodosRecursivo(TipoNo* p, Lista<Par>& resultado) const {
    if (p == nullptr) return;
    TodosRecursivo(p->esq, resultado);
    resultado.Insere_Final(p->item);
    TodosRecursivo(p->dir, resultado);
}

void ArvoreAVL::Converter_Indice(Indice& i) {
    TabelaHash* th = dynamic_cast<TabelaHash*>(&i);
    if (th == nullptr) throw "Classe Indice invalida!";

    Lista<Par> todos_pares;
    Todos(todos_pares);
    for(auto& par : todos_pares)
        th->Inserir(par.valor, par.id_objeto);
}

int ArvoreAVL::FB(TipoNo* p) const {
    return Altura(p->dir) - Altura(p->esq);
}

void ArvoreAVL::AtualizaAltura(TipoNo* p) {
    int maior_altura = 0, esq_altura = Altura(p->esq),
        dir_altura = Altura(p->dir);

    if (esq_altura > dir_altura) maior_altura = esq_altura;
    else maior_altura = dir_altura;

    p->altura = 1 + maior_altura;
}

void ArvoreAVL::RotacaoDireita(TipoNo* &p) {
    TipoNo *f = p->esq; // f vai subir
    p->esq = f->dir; // beta troca de pai
    f->dir = p; // p desce
    AtualizaAltura(p); // quem desceu antes
    AtualizaAltura(f); 
    p = f; // pai agora aponta f
}

void ArvoreAVL::RotacaoEsquerda(TipoNo* &p) {
    TipoNo *f = p->dir; // f vai subir
    p->dir = f->esq; // beta troca de pai
    f->esq = p; // p desce
    AtualizaAltura(p); // quem desceu antes
    AtualizaAltura(f); 
    p = f; // pai agora aponta f
}

void ArvoreAVL::Balanceia(TipoNo* &p) {
    AtualizaAltura(p);
    if (FB(p) == - 2) { // pesa à esquerda
        if (FB(p->esq) > 0) // sinais trocados: ED
            RotacaoEsquerda(p->esq);
        RotacaoDireita(p);
    } else if (FB(p) == 2) { // pesa à direita
        if (FB(p->dir) < 0) // sinais trocados: DE
            RotacaoDireita(p->dir);
        RotacaoEsquerda(p);
    }
}