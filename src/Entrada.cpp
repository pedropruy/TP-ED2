#include "../include/Entrada.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

static RegistroTempo tempo_E, tempo_D, tempo_C,
                     tempo_BP, tempo_BF, tempo_CC,
                     tempo_F, tempo_Z;

void Terminal_Modo(Consultoria& c, std::stringstream& ss) {
    char modo;
    ss >> modo;

    if (modo == 'A' || modo == 'H') {
        auto inicio = std::chrono::high_resolution_clock::now();
        char novo_modo = c.Modo(modo); 
        auto fim = std::chrono::high_resolution_clock::now();
        tempo_E.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
        tempo_E.chamadas++;

        std::cout << "E " << novo_modo << std::endl;
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

    
    auto inicio = std::chrono::high_resolution_clock::now();
    int poder = 0, id_c =  c.Cadastro_Cliente(nome, build, poder);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_C.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_C.chamadas++;

    std::cout << "C " << id_c << " " << poder << std::endl;
}

void Terminal_Encerrar_Cliente(Consultoria& c, std::stringstream& ss) {
    int poder, id_c; ss >> id_c;

    auto inicio = std::chrono::high_resolution_clock::now();
    c.Encerramento_Cliente(id_c, poder);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_D.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_D.chamadas++;

    std::cout << "D " << c.Get_Nome_Cliente(id_c) << " " << poder << std::endl;
}

void Terminal_BPoder_Exato(Consultoria& c, std::stringstream& ss) {
    int poder; ss >> poder;

    
    auto inicio = std::chrono::high_resolution_clock::now();
    Lista<int> busca;
    c.Busca_Poder_Exato(poder, busca);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_BP.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_BP.chamadas++;
    
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
    
    auto inicio = std::chrono::high_resolution_clock::now();
    Lista<Par> busca;
    c.Busca_Faixa_Poder(min, max, busca);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_BF.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_BF.chamadas++;
    
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

void Terminal_Regiao(Consultoria& c, std::stringstream& ss) {
    std::string nome; ss >> nome;
    std::cout << "R " << c.Cadastro_Regiao(nome) << std::endl;
}

void Terminal_Rota(Consultoria& c, std::stringstream& ss) {
    int id_r1, id_r2, custo;
    ss >> id_r1; ss >> id_r2; ss >> custo;
    c.Cadastro_Rota(id_r1, id_r2, custo);

    std::cout << "T " << c.Get_Nome_Regiao(id_r1) << " "
              << c.Get_Nome_Regiao(id_r2) << " " << custo << std::endl;
}

void Terminal_Inverter_Pesquisa_Conectividade(Consultoria& c) {
    bool union_find = c.Inverte_Busca_do_Caminho();
    std::cout << "I ";
    if (union_find) std::cout << "Percorre DSU";
    else std::cout << "Percorre Mapa";
}

void Terminal_Conectividade(Consultoria& c, std::stringstream& ss) {
    int id_r1, id_r2; ss >> id_r1; ss >> id_r2;
    
    auto inicio = std::chrono::high_resolution_clock::now();
    bool conectadas = c.Regioes_Conectadas(id_r1, id_r2);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_CC.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_CC.chamadas++;

    std::cout << "CC " << c.Get_Nome_Regiao(id_r1) << " "
              << c.Get_Nome_Regiao(id_r2);
    if (conectadas) std::cout << " SIM" << std::endl;
    else std::cout << " NAO" << std::endl;
}

void Terminal_Fila_Consultoria(Consultoria& c, std::stringstream& ss) {
    int id_c, prioridade; ss >> id_c; ss >> prioridade;

    auto inicio = std::chrono::high_resolution_clock::now();
    int tamanho_fila = c.Fila_Consultoria({id_c, prioridade});
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_F.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_F.chamadas++;

    std::cout << "F " << tamanho_fila << std::endl;
}

void Terminal_Atendimento(Consultoria& c, std::stringstream& ss) {
    int turnos; ss >> turnos;
    Lista<Filiado> atendidos;

    auto inicio = std::chrono::high_resolution_clock::now();
    // turnos => vira turnos que passaram
    turnos = c.Turnos_Atendimento(turnos, atendidos);
    auto fim = std::chrono::high_resolution_clock::now();
    tempo_Z.total_ms += std::chrono::duration<double, std::milli>(fim - inicio).count();
    tempo_Z.chamadas++;

    std::cout << "Z " << turnos << std::endl;
    
    for (int i = 1; i <= turnos; i++) {
        Filiado& fila = atendidos.Get_Item(i-1); // i começa em 1
        std::cout << "atendimento_" << i << " " << fila.id_cliente
                  << " " << fila.prioridade; 
        if (i < turnos) std::cout << " ";
    }
    if(turnos > 0) std::cout << std::endl;
}

void Terminal_Analise(Consultoria& c, std::stringstream& ss) {
    int qtd_analises; 
    ss >> qtd_analises;
    
    if (qtd_analises == 0) {
        c.Zerar_Analises();

        tempo_E.Zerar(); tempo_D.Zerar(); tempo_C.Zerar();
        tempo_BP.Zerar(); tempo_BF.Zerar(); tempo_CC.Zerar();
        tempo_F.Zerar(); tempo_Z.Zerar();

        std::cout << "ANA Analises zeradas!" << std::endl;
    } else {
        // Encontra o próximo nome disponível: experimento_1.txt, experimento_2.txt...
        int num_exp = 1;
        std::string nome_arquivo;
        while (true) {
            nome_arquivo = "experimento_" + std::to_string(num_exp) + ".txt";
            std::ifstream teste(nome_arquivo);
            if (!teste.good()) break; // Arquivo ainda não existe, podemos usar este nome
            num_exp++;
        }

        std::ofstream arquivo(nome_arquivo);
        if (!arquivo.is_open()) {
            std::cerr << "Erro ao criar arquivo " << nome_arquivo << std::endl;
            return;
        }

        // Salva o buffer e a formatação originais do cout
        std::streambuf* buf_original = std::cout.rdbuf();
        std::ios_base::fmtflags flags_originais = std::cout.flags();
        std::streamsize precisao_original = std::cout.precision();

        // Redireciona todo std::cout para o arquivo
        std::cout.rdbuf(arquivo.rdbuf());

        char TAD;
        for (int i = 0; i < qtd_analises; i++) {
            ss >> TAD;
            if (TAD != 'I' && TAD != 'F' && TAD != 'M' && TAD != 'C') continue;
            
            Analise ana = c.Get_Analise(TAD);
            std::cout << ana << std::endl << std::endl;
        }

        // Evita divisão por zero caso algum comando tenha 0 chamadas
        auto media_ms = [](const RegistroTempo& r) -> double {
            return (r.chamadas > 0) ? (r.total_ms / r.chamadas) : 0.0;
        };

        // Salva os tempos médios no arquivo
        std::cout << "(Tempo Medio por Comando em Milisegundos)" << std::endl;
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "E  - " << media_ms(tempo_E)  << std::endl;
        std::cout << "C  - " << media_ms(tempo_C)  << std::endl;
        std::cout << "D  - " << media_ms(tempo_D)  << std::endl;
        std::cout << "BP - " << media_ms(tempo_BP) << std::endl;
        std::cout << "BF - " << media_ms(tempo_BF) << std::endl;
        std::cout << "CC - " << media_ms(tempo_CC) << std::endl;
        std::cout << "F  - " << media_ms(tempo_F)  << std::endl;
        std::cout << "Z  - " << media_ms(tempo_Z)  << std::endl;

        // Restaura o buffer e a formatação originais do cout
        std::cout.flush();
        std::cout.rdbuf(buf_original);
        std::cout.flags(flags_originais);
        std::cout.precision(precisao_original);
        arquivo.close();

        std::cout << "ANA Arquivo salvo com sucesso!" << std::endl;
    }
    
}

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
    else if (token == "I") Terminal_Inverter_Pesquisa_Conectividade(c);
    else if (token == "CC") Terminal_Conectividade(c, ss);
    else if (token == "F") Terminal_Fila_Consultoria(c, ss);
    else if (token == "Z") Terminal_Atendimento(c, ss);
    else if (token == "ANA") Terminal_Analise(c, ss);
    else std::cout << "Comando invalido!" << std::endl;
}