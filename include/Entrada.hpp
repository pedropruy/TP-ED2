#ifndef ENTRADA_HPP
#define ENTRADA_HPP

#include "Consultoria.hpp"
#include <iostream>

struct RegistroTempo {
    double total_ms = 0.0;
    int chamadas = 0;
};

void Terminal_Modo(Consultoria& c, std::stringstream& ss);

void Terminal_Atributo(Consultoria& c, std::stringstream& ss);

void Terminal_Cliente(Consultoria& c, std::stringstream& ss);

void Terminal_Encerrar_Cliente(Consultoria& c, std::stringstream& ss);

void Terminal_BPoder_Exato(Consultoria& c, std::stringstream& ss);

void Terminal_BFaixa_Poder(Consultoria& c, std::stringstream& ss);

void Terminal_Regiao(Consultoria& c, std::stringstream& ss);

void Terminal_Rota(Consultoria& c, std::stringstream& ss);

void Terminal_Conectividade(Consultoria& c, std::stringstream& ss);

void Terminal_Fila_Consultoria(Consultoria& c, std::stringstream& ss);

void Terminal_Atendimento(Consultoria& c, std::stringstream& ss);

void Comando(Consultoria& c, std::string& linha);

#endif