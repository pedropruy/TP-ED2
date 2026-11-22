#include "../include/Consultoria.hpp"

// Por padrão indice é ArvoreAVL
Consultoria::Consultoria() { indice = new ArvoreAVL(); }
Consultoria::~Consultoria() { delete indice; }

const std::string& Consultoria::Get_Nome_Atributo(int ind) { return atributos[ind].Get_Nome(); }
const int Consultoria::Get_Tamanho_Atributo() { return atributos.Get_Tamanho(); }
const std::string& Consultoria::Get_Nome_Cliente(int ind) { return clientes[ind].Get_Nome(); }
const std::string& Consultoria::Get_Nome_Regiao(int ind) { return mapa.Get_Nome_Regiao(ind); }

char Consultoria::Modo(char modo) {
    bool AVL = (dynamic_cast<ArvoreAVL*>(indice) != nullptr),
         HT = (dynamic_cast<TabelaHash*>(indice) != nullptr);

    // Se o índice já estiver no modo retorna sem fazer nada
    if ((modo == 'A' && AVL) || (modo == 'H' && HT)) return modo;

    if (modo == 'A') {
        ArvoreAVL* avl = new ArvoreAVL();
        indice->Converter_Indice(*avl);
        delete indice;
        indice = avl;
    } else if (modo == 'H') {
        TabelaHash* th = new TabelaHash();
        indice->Converter_Indice(*th);
        delete indice;
        indice = th;
    } else return 'X'; // Modo inválido
    return modo;
}

int Consultoria::Cadastro_Atributo(const std::string& nome) {
    Atributo a(atributos.Get_Tamanho(), nome);
    atributos.Insere_Final(a);
    return a.Get_Id();
}

int Consultoria::Cadastro_Cliente(const std::string& nome, Lista<Par>& valores_atributos, int& poder) {
    Cliente c(clientes.Get_Tamanho(), nome, valores_atributos);
    poder = c.Get_Poder();
    clientes.Insere_Final(c);
    int id_c = c.Get_Id();
    indice->Inserir(poder, id_c);
    return id_c;
}

void Consultoria::Encerramento_Cliente(int ind, int& poder) {
    Cliente& c = clientes[ind];
    poder = c.Get_Poder();
    indice->Remover(poder, c.Get_Id());
    // Não removemos ele de lista, pq seu índice não pode ser reutilizado
}

void Consultoria::Busca_Poder_Exato(int poder, Lista<int>& busca) {
    indice->Buscar(poder, busca);
}

void Consultoria::Busca_Faixa_Poder(int min, int max, Lista<Par>& busca) {
    indice->Faixa(min, max, busca);
}

int Consultoria::Cadastro_Regiao(const std::string& nome) {
    int id_r = mapa.Adicionar_Regiao(nome);
    conjuntos_disjuntos.Make(id_r);
    return id_r;
}

void Consultoria::Cadastro_Rota(int id_regiao1, int id_regiao2, int custo) {
    mapa.Adicionar_Rota(id_regiao1, id_regiao2, custo);
    conjuntos_disjuntos.Union(id_regiao1, id_regiao2);
}

bool Consultoria::Inverte_Union_Find() {
    union_find = !union_find;
    return union_find;
}

bool Consultoria::Regioes_Conectadas(int id_regiao1, int id_regiao2) {
    if (union_find)
        return conjuntos_disjuntos.Find(id_regiao1) == conjuntos_disjuntos.Find(id_regiao2);
    else return mapa.Conectados_Busca(id_regiao1, id_regiao2);
}

int Consultoria::Fila_Consultoria(Filiado cliente) {
    fila.Insere(cliente);
    return fila.Get_Tamanho();
}

int Consultoria::Turnos_Atendimento(int k, Lista<Filiado>& atendidos) {
    atendidos.Limpa();
    while(fila.Get_Tamanho() != 0 && k > 0) {
        Filiado cliente_atendido = fila.Remove();
        atendidos.Insere_Final(cliente_atendido);
        k--;
    }
    return atendidos.Get_Tamanho();
}