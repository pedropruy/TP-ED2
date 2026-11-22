#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include "Indice.hpp"

class Cliente {
    private:
        int id;
        std::string nome;

        Lista<Par> build;
        int poder;
        void Calcular_Poder();
    public:
        Cliente(int _id, std::string _nome, Lista<Par>& _build); Cliente();
        Cliente(const Cliente &c);
        Cliente& operator= (const Cliente &c);
        
        int Get_Id() const;
        const std::string& Get_Nome() const;
        int Get_Poder() const;

        void Set_Id(int _id);
        void Set_Nome(const std::string& _nome);
        void Set_Build(const Lista<Par>& _build);
        
        friend std::ostream& operator<<(std::ostream& os, const Cliente& c);
};

#endif