#include "../include/Entrada.hpp"
#include <fstream>
#include <string>
#include <chrono>

// Definição da estrutura para organizar os lotes de teste
struct LoteTestes {
    int peso;
    Lista<std::string> arquivos;
};

int main() {

    Consultoria consultoria;

    std::string linha;   
    while(std::getline(std::cin, linha)) {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();

        if (linha.empty()) continue; 

        try { Comando(consultoria, linha); }
        catch (char const* e) { std::cout << e << std::endl; }
    }

    return 0;
}