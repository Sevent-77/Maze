# Maze Generation and Navigation

This project implements a maze generation algorithm using a modified version of Eller's algorithm, combined with a character navigation system using ncurses for terminal-based display.

## Features

- **Dynamic Maze Generation**: Creates unique mazes using probabilistic horizontal and vertical connections
- **Character Navigation**: Move through the maze using arrow keys
- **Visual Display**: Uses ncurses for terminal rendering
- **Debug Output**: Generates a text file (`labirinto.txt`) showing the maze's underlying structure
- **Customizable Parameters**: Adjust maze size through preprocessor definitions

## Requirements

- C compiler (GCC recommended)
- Ncurses library
- Linux or Unix-like environment (for ncurses support)

## Compilation and Execution

1. Compile the program:
```bash
gcc main.c -o main -lncurses -lrt
```

2. Run the executable:
```bash
./main
```

3. Use arrow keys to navigate through the maze

## Controls
- **Up Arrow**: Move up
- **Down Arrow**: Move down
- **Left Arrow**: Move left
- **Right Arrow**: Move right

## Code Structure

### Key Components

1. **Preprocessor Definitions**:
   ```c
   #define M_HEIGHT 15                 // Maze matrix height
   #define M_WIDTH 15                  // Maze matrix width
   #define HEIGHT (2*M_HEIGHT)+1       // Actual maze height
   #define WIDTH (2*M_WIDTH)+1         // Actual maze width
   ```

2. **Data Structures**:
   ```c
   typedef struct {
       int x;
       int y;
   } Character;  // Player character structure
   ```

3. **Main Functions**:
   - `init()`: Initializes ncurses environment and maze structure
   - `mazeGen()`: Generates the maze using probabilistic connections
   - `show()`: Displays the maze and character
   - `entryProcess()`: Handles keyboard input for movement

### Algorithm Overview

The maze generation uses a modified Eller's algorithm with these key steps:

1. **Initialize** a matrix with unique set identifiers
2. **Create horizontal connections** between adjacent cells based on probability
3. **Create vertical connections** between rows with controlled randomness
4. **Ensure connectivity** by forcing at least one vertical connection per set
5. **Finalize the maze** by connecting remaining sets in the last row

The algorithm balances randomness and connectivity using two parameters:
- `HORIZONTAL`: Probability of horizontal connections (1-99%)
- `VERTICAL`: Probability of additional vertical connections (1-2%)

## Customization

Modify these parameters in the source code:
```c
// Maze dimensions (affects complexity)
#define M_HEIGHT 15
#define M_WIDTH 15

// Generation parameters (in main())
int HORIZONTAL = rand() % 90 + 1;  // Horizontal connection probability
int VERTICAL = rand() % 2 + 1;     // Vertical connection probability
```

## Debug Output

The program generates `labirinto.txt` showing the numeric set relationships used during maze generation. This helps visualize how the algorithm connects different maze regions.

## License

This code is provided as-is for educational purposes. Feel free to modify and use it in your projects.


# Geração e Navegação em Labirintos

Este projeto implementa um algoritmo de geração de labirintos usando uma versão modificada do algoritmo de Eller, combinado com um sistema de navegação de personagem usando a biblioteca ncurses para exibição no terminal.

## Funcionalidades

- **Geração Dinâmica de Labirintos**: Cria labirintos únicos usando conexões horizontais e verticais probabilísticas
- **Navegação do Personagem**: Movimentação pelo labirinto usando as teclas de seta
- **Exibição Visual**: Utiliza a biblioteca ncurses para renderização no terminal
- **Saída de Depuração**: Gera um arquivo de texto (`labirinto.txt`) mostrando a estrutura subjacente do labirinto
- **Parâmetros Personalizáveis**: Permite ajustar o tamanho do labirinto através de definições no código

## Requisitos

- Compilador C (GCC recomendado)
- Biblioteca ncurses
- Ambiente Linux ou Unix-like (para suporte à ncurses)

## Compilação e Execução

1. Compile o programa:
```bash
gcc main.c -o main -lncurses
```

2. Execute o binário:
```bash
./main
```

3. Use as teclas de seta para navegar pelo labirinto

## Controles
- **Seta para Cima**: Move para cima
- **Seta para Baixo**: Move para baixo
- **Seta para Esquerda**: Move para a esquerda
- **Seta para Direita**: Move para a direita

## Estrutura do Código

### Componentes Principais

1. **Definições no Pré-processador**:
   ```c
   #define M_HEIGHT 15                 // Altura da matriz do labirinto
   #define M_WIDTH 15                  // Largura da matriz do labirinto
   #define HEIGHT (2*M_HEIGHT)+1       // Altura real do labirinto
   #define WIDTH (2*M_WIDTH)+1         // Largura real do labirinto
   ```

2. **Estruturas de Dados**:
   ```c
   typedef struct {
       int x;
       int y;
   } Character;  // Estrutura do personagem
   ```

3. **Funções Principais**:
   - `init()`: Inicializa o ambiente ncurses e a estrutura do labirinto
   - `mazeGen()`: Gera o labirinto usando conexões probabilísticas
   - `show()`: Exibe o labirinto e o personagem
   - `entryProcess()`: Trata a entrada do teclado para movimentação

### Visão Geral do Algoritmo

A geração do labirinto usa uma versão modificada do algoritmo de Eller com os seguintes passos:

1. **Inicializa** uma matriz com identificadores únicos de conjuntos
2. **Cria conexões horizontais** entre células adjacentes baseadas em probabilidade
3. **Cria conexões verticais** entre linhas com aleatoriedade controlada
4. **Garante conectividade** forçando pelo menos uma conexão vertical por conjunto
5. **Finaliza o labirinto** conectando conjuntos restantes na última linha

O algoritmo balanceia aleatoriedade e conectividade usando dois parâmetros:
- `HORIZONTAL`: Probabilidade de conexões horizontais (1-99%)
- `VERTICAL`: Probabilidade de conexões verticais adicionais (1-2%)

## Personalização

Modifique os seguintes parâmetros no código-fonte:
```c
// Dimensões do labirinto (afetam a complexidade)
#define M_HEIGHT 15
#define M_WIDTH 15

// Parâmetros de geração (na função main())
int HORIZONTAL = rand() % 90 + 1;  // Probabilidade de conexão horizontal
int VERTICAL = rand() % 2 + 1;     // Probabilidade de conexão vertical
```

## Saída de Depuração

O programa gera o arquivo `labirinto.txt` mostrando as relações numéricas dos conjuntos usados durante a geração. Isso ajuda a visualizar como o algoritmo conecta diferentes regiões do labirinto.

## Explicação Detalhada do Funcionamento

### Inicialização (`init()`)
- Configura o ambiente ncurses para controle do terminal
- Define a posição inicial do personagem no canto superior esquerdo
- Preenche a matriz do labirinto com:
  - `#` para paredes externas
  - `*` para paredes internas potenciais
  - ` ` (espaço) para caminhos livres

### Geração do Labirinto (`mazeGen()`)
1. **Matriz de Suporte**: Cria uma matriz numérica onde cada célula pertence a um "conjunto"
2. **Conexões Horizontais**:
   - Percorre cada linha unindo conjuntos adjacentes aleatoriamente
   - A probabilidade é controlada pelo parâmetro `HORIZONTAL`
   - Quando conjuntos são unidos, remove a parede entre eles
3. **Conexões Verticais**:
   - Para cada conjunto na linha atual:
     - Seleciona pelo menos uma célula para conectar com a linha abaixo
     - Conecta outras células do mesmo conjunto com probabilidade `VERTICAL`
   - Garante que cada conjunto tenha pelo menos uma passagem vertical
4. **Linha Final**:
   - Conecta todos os conjuntos restantes na última linha
   - Garante que não existam becos sem saída

### Navegação (`entryProcess()`)
- Detecta pressionamento das teclas de seta
- Verifica se a movimentação é válida (não colide com paredes)
- Atualiza a posição do personagem somente se o caminho estiver livre

### Exibição (`show()`)
- Desenha o labirinto completo na tela
- Mostra o personagem como `o` na posição atual
- Atualiza a tela a cada movimento

## Licença

Este código é fornecido como está para fins educacionais. Sinta-se à vontade para modificá-lo e usá-lo em seus projetos.