#include "../include/Cliente.hpp"
#include <iostream>

Cliente::Cliente(int _id, std::string _nome,  Lista<int>& _build) :
                 id(_id), nome(_nome), build(_build), poder(0) {
    Calcular_Poder();
}
Cliente::Cliente() : id(-1), nome("ERRO"), poder(0) {}
Cliente::Cliente(const Cliente &c) : id(c.id), nome(c.nome), build(c.build), poder(c.poder) {}
Cliente& Cliente::operator= (const Cliente &c) {
    if (this == &c) return *this;
    this->id = c.id;
    this->nome = c.nome;
    this->build = c.build;
    this->poder = c.poder;
    return *this; 
}

int Cliente::Get_Id() const { return id; }
const std::string& Cliente::Get_Nome() const { return nome; }
int Cliente::Get_Poder() const { return poder; }

void Cliente::Set_Id(int _id) { id = _id; }
void Cliente::Set_Nome(const std::string& _nome) { nome = _nome; }
void Cliente::Set_Build(const Lista<int>& _build) {
    build = _build;
    Calcular_Poder();
}

void Cliente::Calcular_Poder() {
    this->poder = 0;

    for(int i = 0; i < build.Get_Tamanho(); i++)
        this->poder += build[i];
}

std::ostream& operator<<(std::ostream& os, const Cliente& c) {
    os << c.id << ":" << c.nome << ":" << c.poder;
    c.build.Imprime();

    return os;
}