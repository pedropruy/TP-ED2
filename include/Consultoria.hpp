#ifndef CONSULTORIA_HPP
#define CONSULTORIA_HPP

#include "Atributo.hpp"
#include "Cliente.hpp"
#include "Heap.hpp"
#include "Mapa.hpp"
#include "DSU.hpp"

class Consultoria {
    public:
        Consultoria(); ~Consultoria();
        Analise Get_Analise(char TAD); //ANA, LEGAL NÉ?
        void Zerar_Analises();
        // Devolvendo const std::string& para evitar cópia desnecessária de strings
        const std::string& Get_Nome_Atributo(int ind);
        const int Get_Tamanho_Atributo();
        const std::string& Get_Nome_Cliente(int ind);
        const std::string& Get_Nome_Regiao(int ind);
        char Modo(char modo); // E
        int Cadastro_Atributo(const std::string& nome); // A
        int Cadastro_Cliente(const std::string& nome, Lista<Par>& valores_atributos, int& poder); // C
        void Encerramento_Cliente(int ind, int& poder); // D
        void Busca_Poder_Exato(int poder, Lista<int>& busca); // BP
        void Busca_Faixa_Poder(int min, int max, Lista<Par>& busca); // BF
        int Cadastro_Regiao(const std::string& nome); // R
        void Cadastro_Rota(int id_regiao1, int id_regiao2, int custo); // T
        bool Inverte_Busca_do_Caminho(); // I
        bool Regioes_Conectadas(int id_regiao1, int id_regiao2); // CC
        int Fila_Consultoria(Filiado cliente); // F
        int Turnos_Atendimento(int k, Lista<Filiado>& atendidos); // Z
    private:
        Lista<Atributo> atributos;
        Lista<Cliente> clientes;
        Indice* indice;
        Heap fila;

        Mapa mapa;
        DSU conjuntos_disjuntos;
        bool union_find = false;
};

#endif