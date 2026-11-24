import random
import argparse

# Script gerador de entradas criado pelo Gemini!

def gerar_entradas(args):
    random.seed(args.semente)
    
    # Mantém o estado válido da simulação para respeitar as regras de negócio do TP2:
    # - Um cliente não é encerrado duas vezes
    # - Um cliente encerrado não entra na fila
    # - Um cliente que está aguardando na fila não é encerrado
    clientes_ativos = set()
    na_fila = {}  # id_cliente -> contagem de ocorrências na fila
    fila_simulada = []  # lista de (-prioridade, id_cliente) para simular atendimentos Z
    proximo_id_cliente = 0
    poderes_existentes = []

    with open(args.saida, 'w') as f:
        # 1. Modo inicial do índice (A ou H)
        f.write(f"E {args.modo}\n")
        
        # 2. Cadastro de atributos (nomes apenas com letras, sem espaços)
        for i in range(args.T):
            f.write(f"A Atributo{chr(65 + (i % 26))}{i}\n")
            
        # 3. Cadastro de regiões e rotas (controlando tamanho V e densidade)
        for i in range(args.V):
            f.write(f"R Regiao{i}\n")
            
        max_rotas_possiveis = (args.V * (args.V - 1)) // 2
        qtd_rotas = min(max_rotas_possiveis, int(max_rotas_possiveis * args.densidade))
        rotas_geradas = set()
        
        while len(rotas_geradas) < qtd_rotas:
            u = random.randint(0, args.V - 1)
            v = random.randint(0, args.V - 1)
            if u != v:
                aresta = (min(u, v), max(u, v))
                rotas_geradas.add(aresta)
                
        for u, v in rotas_geradas:
            custo = random.randint(1, 50)
            f.write(f"T {u} {v} {custo}\n")
            
        # 4. Carga inicial de clientes (C)
        for _ in range(args.N):
            k = min(args.T, max(1, int(random.gauss(args.build_media, 2))))
            atributos_escolhidos = random.sample(range(args.T), k=k)
            
            pares_str = []
            poder_total = 0
            for attr_id in atributos_escolhidos:
                # Permite controlar a dispersão de chaves distintas no índice via --faixa_valor
                val = random.randint(-args.faixa_valor, args.faixa_valor)
                pares_str.append(f"{attr_id} {val}")
                poder_total += val
                
            f.write(f"C Cliente{proximo_id_cliente} {k} " + " ".join(pares_str) + "\n")
            clientes_ativos.add(proximo_id_cliente)
            poderes_existentes.append(poder_total)
            proximo_id_cliente += 1

        # Define se CC usará Mapa em vez do padrão DSU
        if args.usar_union_find:
            f.write("I\n")

        # 5. Carga transacional mista (Atualizações vs Consultas)
        p_upd = args.perc_atualizacao
        p_qry = 1.0 - p_upd
        
        # Proporção interna das atualizações respeitando a rotatividade (--perc_remocao)
        p_rem = args.perc_remocao
        p_ins = 1.0 - p_rem
        
        # Dentro das atualizações: 60% vão para o Índice (C e D) e 40% para a Fila (F e Z)
        comandos = ['C', 'D', 'F', 'Z', 'BP', 'BF', 'CC']
        pesos = [
            0.60 * p_ins * p_upd,  # C (Cadastro)
            0.60 * p_rem * p_upd,  # D (Encerramento)
            0.20 * p_upd,          # F (Entrada na fila)
            0.20 * p_upd,          # Z (Atendimento)
            0.40 * p_qry,          # BP (Busca por poder exato)
            0.40 * p_qry,          # BF (Busca por faixa de poder)
            0.20 * p_qry           # CC (Conectividade)
        ]
        
        for _ in range(args.operacoes):
            if args.migrar_final:
                break

            cmd = random.choices(comandos, weights=pesos)[0]
            
            # Se sorteou D mas não há clientes elegíveis (ativos e fora da fila), faz C
            elegiveis_remocao = [cid for cid in clientes_ativos if na_fila.get(cid, 0) == 0]
            if cmd == 'D' and not elegiveis_remocao:
                cmd = 'C'
                
            # Se sorteou F mas não há clientes ativos, faz C
            if cmd == 'F' and not clientes_ativos:
                cmd = 'C'

            if cmd == 'C':
                k = min(args.T, max(1, int(random.gauss(args.build_media, 2))))
                atributos_escolhidos = random.sample(range(args.T), k=k)
                
                pares_str = []
                poder_total = 0
                for attr_id in atributos_escolhidos:
                    val = random.randint(-args.faixa_valor, args.faixa_valor)
                    pares_str.append(f"{attr_id} {val}")
                    poder_total += val
                    
                f.write(f"C Cliente{proximo_id_cliente} {k} " + " ".join(pares_str) + "\n")
                clientes_ativos.add(proximo_id_cliente)
                poderes_existentes.append(poder_total)
                proximo_id_cliente += 1
                
            elif cmd == 'D':
                cid = random.choice(elegiveis_remocao)
                f.write(f"D {cid}\n")
                clientes_ativos.remove(cid)
                
            elif cmd == 'F':
                cid = random.choice(list(clientes_ativos))
                prioridade = random.randint(1, 100)
                f.write(f"F {cid} {prioridade}\n")
                na_fila[cid] = na_fila.get(cid, 0) + 1
                fila_simulada.append((-prioridade, cid))
                
            elif cmd == 'Z':
                k_atend = random.randint(1, 5)
                f.write(f"Z {k_atend}\n")
                # Atualiza a simulação da fila para saber quem saiu e pode ser encerrado no futuro
                fila_simulada.sort()
                atendidos = fila_simulada[:k_atend]
                fila_simulada = fila_simulada[k_atend:]
                for _, cid in atendidos:
                    na_fila[cid] -= 1
                    if na_fila[cid] <= 0:
                        del na_fila[cid]
                        
            elif cmd == 'BP':
                if poderes_existentes and random.random() < 0.8:
                    poder_busca = random.choice(poderes_existentes)
                else:
                    poder_busca = random.randint(-args.faixa_valor * args.build_media, args.faixa_valor * args.build_media)
                f.write(f"BP {poder_busca}\n")
                
            elif cmd == 'BF':
                amplitude = max(1, int(args.faixa_valor * args.build_media * args.largura_faixa))
                centro = random.choice(poderes_existentes) if poderes_existentes else 0
                p_min = centro - amplitude // 2
                p_max = centro + amplitude // 2
                f.write(f"BF {p_min} {p_max}\n")
                
            elif cmd == 'CC':
                if args.V >= 2:
                    r1, r2 = random.sample(range(args.V), 2)
                    f.write(f"CC {r1} {r2}\n")

        # 6. Troca de modo no meio/final se solicitado (--migrar_final)
        if args.migrar_final:
            modo_oposto = 'H' if args.modo == 'A' else 'A'
            f.write("ANA 1 I\nANA 0\n")
            f.write(f"E {modo_oposto}\n")
            f.write("ANA 1 I\n")
        else:
        # 7. Comando final para salvar as estatísticas e tempos no arquivo experimento_X.txt
            f.write("ANA 4 I F M C\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Gerador de Entradas para TP2 - A Consultoria do Blibblon")
    parser.add_argument('--modo', type=str, choices=['A', 'H'], default='A', help='Modo inicial do índice (A=AVL, H=Hash)')
    parser.add_argument('--N', type=int, default=1000, help='Número de clientes iniciais')
    parser.add_argument('--T', type=int, default=20, help='Número de atributos cadastrados')
    parser.add_argument('--V', type=int, default=200, help='Número de regiões no mapa')
    parser.add_argument('--densidade', type=float, default=0.25, help='Densidade de rotas do mapa (0.0 a 1.0)')
    parser.add_argument('--build_media', type=int, default=5, help='Quantidade média de atributos informados por build')
    parser.add_argument('--faixa_valor', type=int, default=50, help='Amplitude de valores dos atributos (controla colisões/chaves distintas)')
    parser.add_argument('--largura_faixa', type=float, default=0.10, help='Tamanho relativo da janela de busca BF (0.0 a 1.0)')
    parser.add_argument('--operacoes', type=int, default=2500, help='Quantidade de comandos transacionais')
    parser.add_argument('--perc_atualizacao', type=float, default=0.50, help='Proporção de atualizações (C, D, F, Z) vs consultas (BP, BF, CC)')
    parser.add_argument('--perc_remocao', type=float, default=0.50, help='Taxa de rotatividade: proporção de remoções D dentro do índice (0.0 = só insere, 0.5 = 50%% insere / 50%% remove)')
    parser.add_argument('--usar_union_find', action='store_true', help='Envia comando I para inverter o bool do union_find (inicia em false)')
    parser.add_argument('--migrar_final', action='store_true', help='Envia comando E trocando o modo no final para medir o custo de migração')
    parser.add_argument('--semente', type=int, default=13, help='Semente de aleatoriedade')
    parser.add_argument('--saida', type=str, default='teste_exp.txt', help='Arquivo de saída')
    
    args = parser.parse_args()
    gerar_entradas(args)
    print(f"Arquivo '{args.saida}' gerado com sucesso.")
    print(f"Modo: {args.modo} | Clientes iniciais: {args.N} | Regiões: {args.V} (Densidade: {args.densidade})")
    print(f"Carga: {args.perc_atualizacao*100:.0f}% Atualizações (Rotatividade D: {args.perc_remocao*100:.0f}%) / {(1.0-args.perc_atualizacao)*100:.0f}% Consultas.")