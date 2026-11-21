#ifndef ATRIBUTO_HPP
#define ATRIBUTO_HPP

#include <string>

class Atributo {
    private:
        int id;
        std::string nome;
    public:
        Atributo(int _id, std::string _nome); Atributo();
        Atributo(const Atributo &a);
        Atributo& operator= (const Atributo &a);
        
        int Get_Id() const;
        const std::string& Get_Nome() const;
        void Set_Id(int _id);
        void Set_Nome(const std::string& _nome);
        
        friend std::ostream& operator<<(std::ostream& os, const Atributo& a);
};

#endif