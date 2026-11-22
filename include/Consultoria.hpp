#ifndef CONSULTORIA_HPP
#define CONSULTORIA_HPP

#include "Atributo.hpp"
#include "Cliente.hpp"
#include "Heap.hpp"

class Consultoria {
    public:
        Consultoria(); ~Consultoria();
        // Devolvendo const std::string& para evitar cópia desnecessária de strings
        const std::string& Get_Nome_Atributo(int ind);
        const int Get_Tamanho_Atributo();
        const std::string& Get_Nome_Cliente(int ind);
        char Modo(char modo); // E
        int Cadastro_Atributo(const std::string& nome); // A
        int Cadastro_Cliente(const std::string& nome, Lista<Par>& valores_atributos, int& poder); // C
        void Encerramento_Cliente(int ind, int& poder); // D
        void Busca_Poder_Exato(int poder, Lista<int>& busca); // BP
        void Busca_Faixa_Poder(int min, int max, Lista<Par>& busca); // BF
        int Fila_Consultoria(Filiado cliente); // F
        int Turnos_Atendimento(int k, Lista<Filiado>& atendidos); // Z
        
    private:
        Lista<Atributo> atributos;
        Lista<Cliente> clientes;
        Indice* indice;
        Heap fila;
};

#endif