# Geração e Navegação de Labirintos com Perseguição

Este projeto implementa um algoritmo de geração de labirintos usando uma versão modificada do algoritmo de Eller, combinado com um sistema de navegação de personagens e um inimigo perseguidor. O jogo utiliza ncurses para exibição em terminal e inclui múltiplos níveis, sistema de vidas e IA que persegue o jogador.

## Funcionalidades

- **Geração Dinâmica de Labirintos**: Cria labirintos únicos usando conexões probabilísticas horizontais e verticais
- **Navegação de Personagens**: Movimentação pelo labirinto usando teclas direcionais
- **IA Perseguidora**: Inimigo que segue o jogador usando BFS (Buscas em Largura)
- **Sistema de Níveis**: Labirintos progressivamente mais difíceis com níveis crescentes
- **Sistema de Vidas**: Jogador tem múltiplas vidas, perdidas quando capturado pelo inimigo
- **Exibição Visual**: Usa ncurses para renderização em terminal com suporte a cores
- **Rastro de Visitação**: Opção para mostrar posições visitadas (ativar com 't')
- **Métricas de Desempenho**: Exibição em tempo real do nível e vidas restantes
- **Parâmetros Customizáveis**: Ajuste de tamanho do labirinto e dificuldade via definições de pré-processador

## Requisitos

- Compilador C (GCC recomendado)
- Biblioteca ncurses (suporte a caracteres largos)
- Ambiente Linux ou Unix-like (para suporte ao ncurses)

## Compilação e Execução

1. Compile o programa:
```bash
gcc main.c -o main -lncursesw -lrt
```

2. Execute o binário:
```bash
./main
```

3. Use as teclas direcionais para navegar pelo labirinto

## Controles
- **Teclas Direcionais**: Movimentam o jogador
- **R**: Gera novo labirinto (reinicia nível atual)
- **T**: Ativa/desativa rastro (mostra posições visitadas)
- **Z**: Ativa/desativa câmera lenta para movimento do inimigo (para depuração)

## Elementos do Jogo

- **Jogador**: Representado por `o` (amarelo)
- **Inimigo (Perseguidor)**: Representado por `x` (vermelho) - aparece após 3 segundos
- **Entrada**: Representada por `+` (verde)
- **Saída**: Representada por `_` (verde) - alcance para avançar de nível

## Mecânicas de Jogo

- O jogador começa na entrada e deve alcançar a saída
- Cada nível aumenta a velocidade do inimigo (dificuldade)
- O inimigo persegue o jogador usando BFS, garantindo o caminho mais curto
- Se o inimigo capturar o jogador, perde-se uma vida
- Quando o jogador alcança a saída:
  - Um novo labirinto é gerado (próximo nível)
  - Jogador ganha uma vida (até máximo de 10)
  - Velocidade do inimigo aumenta 8%
- O jogo termina quando o jogador perde todas as vidas

## Estrutura do Código

### Componentes Principais

1. **Estruturas de Dados**:
   ```c
   typedef struct {
       int x;
       int y;
   } Coordinates;
   
   typedef struct {
       int interval, entranceTime, life;
       bool alive;
       Coordinates position;
       struct timespec lastEvent;
   } Character;
   ```

2. **Variáveis Globais**:
   - `maze[HEIGHT][WIDTH]`: Armazena a estrutura do labirinto
   - `visited[HEIGHT][WIDTH]`: Rastreia posições visitadas pelo jogador
   - `actor`: Personagem do jogador
   - `stalker`: Inimigo perseguidor
   - `enterDoor`, `leaveDoor`: Coordenadas de entrada e saída

3. **Funções Principais**:
   - `init()`: Inicializa ncurses, pares de cores e estrutura do labirinto
   - `mazeGen()`: Gera labirinto usando algoritmo de Eller modificado
   - `show()`: Exibe labirinto, jogador, inimigo e portas com cores
   - `entryProcess()`: Processa entrada de teclado para movimentação
   - `Stalker()`: Controla comportamento e movimento do inimigo
   - `BFS()`: Implementa Busca em Largura para pathfinding do inimigo
   - `genNewMaze()`: Gera novo labirinto para próximo nível

### Visão Geral dos Algoritmos

**Geração de Labirinto** (Algoritmo de Eller Modificado):
1. Inicializa matriz com identificadores únicos de conjuntos
2. Cria conexões horizontais entre células adjacentes baseado em probabilidade
3. Cria conexões verticais entre linhas com aleatoriedade controlada
4. Garante conectividade forçando pelo menos uma conexão vertical por conjunto
5. Finaliza labirinto conectando conjuntos remanescentes na última linha

**IA do Inimigo** (Busca em Largura - BFS):
1. Usa BFS baseado em fila para encontrar caminho mais curto até o jogador
2. Explora todos os caminhos possíveis no labirinto
3. Rastreia caminho percorrido usando matriz `cameFrom`
4. Executa primeiro passo do caminho mais curto em cada intervalo de movimento

## Customização

Modifique estes parâmetros no código-fonte:
```c
// Dimensões do labirinto
#define M_HEIGHT 8
#define M_WIDTH 8

// Velocidade do inimigo (diminui com o nível, tornando-o mais rápido)
speed -= 0.08; // Dentro de genNewMaze()

// Atraso inicial para aparecimento do inimigo (segundos)
getElapsedTime(&lastMazeGen, 3.0) // Em createStalker()
```

## Métricas de Desempenho

O jogo exibe informações em tempo real abaixo do labirinto:
- Número do nível atual
- Vidas restantes (barra de saúde visual)
- Velocidade do inimigo aumenta a cada nível

## Recursos de Depuração

- **Modo Rastro**: Ative/desative com 't' para ver posições visitadas (marcadas com '.')
- **Câmera Lenta**: Ative/desative com 'z' para desacelerar movimento do inimigo (para observação)
- **Exibição de Vidas**: Vidas são mostradas como uma linha de símbolos '@' abaixo do labirinto

## Licença

Este código é fornecido "como está" para fins educacionais. Sinta-se à vontade para modificar e usá-lo em seus projetos.