#include "../include/Entrada.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

static RegistroTempo tempo_E, tempo_M, tempo_F, tempo_Z,
                     tempo_D, tempo_LI, tempo_LA, tempo_LH,
                     tempo_LF, tempo_Q;

void Terminal_Modo(Consultoria& c, std::stringstream& ss) {
    char modo;
    ss >> modo;

    if (modo == 'A' || modo == 'H') {
        //long long Bytes_Antes = c.Get_Bytes_Matriz();
        auto inicio = std::chrono::high_resolution_clock::now();
        
        char novo_modo = c.Modo(modo); 
        
        auto fim = std::chrono::high_resolution_clock::now();
        tempo_E.total_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();

        std::cout << "E " << novo_modo << std::endl;
        /*std::cout << "Tempo E - " << tempo_E.total_ms << std::endl;

        long long Bytes_Depois = j.Get_Bytes_Matriz();
        std::cout << "B_Antes: " << Bytes_Antes << std::endl
                  << "B_Depois: " << Bytes_Depois << std::endl
                  << "Pico_Estimado: " << (Bytes_Antes + Bytes_Depois) << std::endl
                  << j.Get_Analise_Catalogo() << std::endl;*/
    } else std::cout << "Modo invalido!" << std::endl;
}

void Terminal_Atributo(Consultoria& c, std::stringstream& ss) {
    std::string nome;
    ss >> nome;
    std::cout << "A " << c.Cadastro_Atributo(nome) << std::endl;
}

void Terminal_Cliente(Consultoria& c, std::stringstream& ss) {
    std::string nome; ss >> nome;
    // Lista build terá o tamanho exato de todos os atributos
    Lista<Par> build;
    for(int i = 0; i < c.Get_Tamanho_Atributo(); i++)
        build.Insere_Final({0,0});

    int k, id_a, valor_a; ss >> k;
    for(int i = 0; i < k; i++) {
        ss >> id_a; ss >> valor_a;
        build[id_a] = {id_a, valor_a};
    }    

    int poder = 0, id_c =  c.Cadastro_Cliente(nome, build, poder);
    std::cout << "C " << id_c << " " << poder << std::endl;
}

void Terminal_Encerrar_Cliente(Consultoria& c, std::stringstream& ss) {
    int poder, id_c; ss >> id_c;
    c.Encerramento_Cliente(id_c, poder);
    std::cout << "D " << c.Get_Nome_Cliente(id_c) << " " << poder << std::endl;
}

void Terminal_BPoder_Exato(Consultoria& c, std::stringstream& ss) {
    int poder; ss >> poder;
    Lista<int> busca;
    c.Busca_Poder_Exato(poder, busca);
    
    std::cout << "BP " << poder;
    // Caso não tenha encontrado nenhum
    if (busca.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl; return;
    }

    int id_c;
    for(int i = 0; i < busca.Get_Tamanho(); i++) {
        id_c = busca[i];
        std::cout << " cliente_" << i+1 << " " << id_c;
    }
    std::cout << std::endl;
}

void Terminal_BFaixa_Poder(Consultoria& c, std::stringstream& ss) {
    int min, max; ss >> min; ss >> max;
    Lista<Par> busca;
    c.Busca_Faixa_Poder(min, max, busca);
    
    std::cout << "BF " << min << " " << max;
    // Caso não tenha encontrado nenhum
    if (busca.Get_Tamanho() == 0) {
        std::cout << " VAZIO" << std::endl; return;
    }

    for(int i = 0; i < busca.Get_Tamanho(); i++) {
        Par par = busca[i];
        std::cout << " cliente_" << i+1 << " " << par.id_objeto
                  << " " << par.valor;
    }
    std::cout << std::endl;
}

void Terminal_Regiao(Consultoria& c, std::stringstream& ss) {}

void Terminal_Rota(Consultoria& c, std::stringstream& ss) {}

void Terminal_Conectividade(Consultoria& c, std::stringstream& ss) {}

void Terminal_Fila_Consultoria(Consultoria& c, std::stringstream& ss) {}

void Terminal_Atendimento(Consultoria& c, std::stringstream& ss) {}

void Comando(Consultoria& c, std::string& linha) {
    std::string token; 
    std::stringstream ss(linha);
    ss >> token; //lê a primeira palavra da linha

    if (token == "E") Terminal_Modo(c, ss);
    else if (token == "A") Terminal_Atributo(c, ss);
    else if (token == "C") Terminal_Cliente(c, ss);
    else if (token == "D") Terminal_Encerrar_Cliente(c, ss);
    else if (token == "BP") Terminal_BPoder_Exato(c, ss);
    else if (token == "BF") Terminal_BFaixa_Poder(c, ss);
    else if (token == "R") Terminal_Regiao(c, ss);
    else if (token == "T") Terminal_Rota(c, ss);
    else if (token == "CC") Terminal_Conectividade(c, ss);
    else if (token == "F") Terminal_Fila_Consultoria(c, ss);
    else if (token == "Z") Terminal_Atendimento(c, ss);
    else std::cout << "Comando invalido!" << std::endl;
}