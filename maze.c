#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define M_HEIGHT 15                 //Tamanho da matriz do labirinto
#define M_WIDTH 30                  //Tamanho da matriz do labirinto
#define VERTICAL 20                  //Tamanho da matriz do labirinto
#define HORIZONTAL 80                 //Tamanho da matriz do labirinto
#define HEIGHT (2*M_HEIGHT)+1       //Tamanho do labirinto
#define WIDTH (2*M_WIDTH)+1         //Tamanho do labirinto

typedef struct {
    int x;                          //Struct do personagem
    int y;
} Character;

typedef struct {
    int x;                          //Struct das portas
    int y;
} Door;

Door enterDoor;
Door leaveDoor;
Character actor;                    //Definindo o personagem
char maze[HEIGHT][WIDTH];           //Criando o labirinto
bool trail_active = false; // Controle do rastro (ativar/desativar)
bool visited[HEIGHT][WIDTH] = {false}; // Rastrear posições visitadas
//int HORIZONTAL;
//int VERTICAL;

void init();                        //Definindo as funções
void show();
void entryProcess();
void mazeGen();
void clearTrail();
void randomDoor();
void genNewMaze();

int main() {
    srand(time(NULL));
    //HORIZONTAL = rand() % 100 + 1; //Parâmetro de horinzontalidade e de verticalidade
    //VERTICAL = rand() % 100 + 1;
    init();
    mazeGen();

    //randomDoor();
    while (1) {
        show();                         //loop de execução
        entryProcess();
    }
    endwin();
    return 0;
}
void genNewMaze(){
    clearTrail(); // Limpa o rastro
            // Reinicializa parâmetros e gera novo labirinto
            //HORIZONTAL = rand() % 100 + 1;
            //VERTICAL = rand() % 100 + 1;
            init();
            mazeGen();
}

void randomDoor() {
    int entryWall = rand() % 4 + 1;
    int exitWall = 0;

    while (1) {
        exitWall = rand() % 4 + 1;
        if (entryWall != exitWall)
            break;
    }

    // Entrada
    switch (entryWall) {
        case 1: // topo
            enterDoor.x = (rand() % M_WIDTH) * 2 + 1;
            enterDoor.y = 0;
            break;
        case 2: // direita
            enterDoor.x = WIDTH - 1;
            enterDoor.y = (rand() % M_HEIGHT) * 2 + 1;
            break;
        case 3: // baixo
            enterDoor.x = (rand() % M_WIDTH) * 2 + 1;
            enterDoor.y = HEIGHT - 1;
            break;
        case 4: // esquerda
            enterDoor.x = 0;
            enterDoor.y = (rand() % M_HEIGHT) * 2 + 1;
            break;
    }

    // Saída
    switch (exitWall) {
        case 1:
            leaveDoor.x = (rand() % M_WIDTH) * 2 + 1;
            leaveDoor.y = 0;
            break;
        case 2:
            leaveDoor.x = WIDTH - 1;
            leaveDoor.y = (rand() % M_HEIGHT) * 2 + 1;
            break;
        case 3:
            leaveDoor.x = (rand() % M_WIDTH) * 2 + 1;
            leaveDoor.y = HEIGHT - 1;
            break;
        case 4:
            leaveDoor.x = 0;
            leaveDoor.y = (rand() % M_HEIGHT) * 2 + 1;
            break;
    }

    // maze[enterDoor.y][enterDoor.x] = ' ';
    // maze[leaveDoor.y][leaveDoor.x] = ' ';
}


void entryProcess() {
    int key = getch();
    switch (key) {
        case 'w':
        case 'W':
        case KEY_UP:
            if (maze[actor.y - 1][actor.x] == ' ') {
                visited[actor.y][actor.x] = true; // Marca posição atual
                actor.y--;
            }else if (maze[actor.y - 1][actor.x] == '_'){
                genNewMaze();
            }
            break;
        case 'a':
        case 'A':
        case KEY_LEFT:
            if (maze[actor.y][actor.x - 1] == ' ') {
                visited[actor.y][actor.x] = true;
                actor.x--;
            }else if (maze[actor.y][actor.x-1] == '_'){
                genNewMaze();
            }
            break;
        case 's':
        case 'S':
        case KEY_DOWN:
            if (maze[actor.y + 1][actor.x] == ' ') {
                visited[actor.y][actor.x] = true;
                actor.y++;
            }else if (maze[actor.y + 1][actor.x] == '_'){
                genNewMaze();
            }
            break;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            if (maze[actor.y][actor.x + 1] == ' ') {
                visited[actor.y][actor.x] = true;
                actor.x++;
            }else if (maze[actor.y][actor.x+1] == '_'){
                genNewMaze();
            }
            break;
        case 'r':
        case 'R':
            genNewMaze();
            break;
        case 't': // Tecla 't' alterna o rastro
        case 'T':
            trail_active = !trail_active;
            break;
    }
}

void show() {
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            if (i == actor.y && j == actor.x) {
                mvaddch(i, j, 'o');
            } else if (i == enterDoor.y && j == enterDoor.x) {
                mvaddch(i, j, '+');
            } else if (i == leaveDoor.y && j == leaveDoor.x) {
                mvaddch(i, j, '_');
            } else if (trail_active && visited[i][j] && maze[i][j] == ' ') {
                mvaddch(i, j, '.'); // Exibe rastro
            } else {
                mvaddch(i, j, maze[i][j]);
            }
        }
    }
    // Exibe status do rastro
    mvprintw(HEIGHT + 1, 0, "Rastro: %s (T para alternar)", 
            trail_active ? "ATIVO  " : "INATIVO");
    mvprintw(HEIGHT + 2, 0, "Horizontal: %d",HORIZONTAL);
    mvprintw(HEIGHT + 3, 0, "Vertical: %d",VERTICAL);
    mvprintw(HEIGHT + 4, 0, "X: %d Y: %d",enterDoor.x,enterDoor.y);
    mvprintw(HEIGHT + 5, 0, "X: %d Y: %d",leaveDoor.x,leaveDoor.y);
    refresh();
}

void mazeGen() {
    int number = 1;
    int mazeMatrix[M_HEIGHT + 1][M_WIDTH]; //Cria a matriz

    //Limpa a matriz definindo tudo para 0
    for (int i = 0; i < M_HEIGHT; i++)
        for (int j = 0; j < M_WIDTH; j++)
            mazeMatrix[i][j] = 0;

    for (int i = 0; i < M_HEIGHT - 1; i++) {
        //Cria um array para armazenar o numero de vezes que um número aparece
        int arr[M_WIDTH * M_WIDTH] = {0};
        
        //Cria a matrix que de suporte para o labirinto
        for (int j = 0; j < M_WIDTH; j++)
            if (mazeMatrix[i][j] == 0)
                //Adiciona o numero a matriz
                mazeMatrix[i][j] = number++;

        //Une conjuntos usando o parâmetro de aleatoriedade
        for (int j = 1; j < M_WIDTH; j++) {
            int N = rand() % 100 + 1;
            if (N < HORIZONTAL && mazeMatrix[i][j] != mazeMatrix[i][j - 1]) {
                int oldSet = mazeMatrix[i][j];
                int newSet = mazeMatrix[i][j - 1];
                for (int k = 0; k < M_WIDTH; k++)
                    if (mazeMatrix[i][k] == oldSet)
                        mazeMatrix[i][k] = newSet;
            }
        }

        //Se vários elementos são de um mesmo conjunto, eles são unidos
        for (int k = 1; k < M_WIDTH; k++)
            if (mazeMatrix[i][k] == mazeMatrix[i][k - 1])
                maze[i * 2 + 1][k * 2] = ' ';

        //Adiciona os conjuntos ao vetor
        for (int j = 0; j < M_WIDTH; j++)
            arr[mazeMatrix[i][j]]++;

        //Verifica o vetor inteirto para ver se o grupo ira se unir com a próxima linha
        for (int j = 0; j < M_WIDTH * M_WIDTH; j++) {
            if (arr[j] == 0) continue;
            //Se só tiver 1 elemento, com certeza vai se unir
            if (arr[j] == 1) {
                for (int k = M_WIDTH - 1; k >= 0; k--) {
                    if (mazeMatrix[i][k] == j && i < M_HEIGHT - 1) {
                        mazeMatrix[i + 1][k] = j;
                        maze[(i * 2) + 2][(k * 2) + 1] = ' ';
                        break;
                    }
                }
            
            } else {    //Se tiver mais de um, aleatoriamente vai juntar ou não
                int indices[M_WIDTH], count = 0;
                for (int k = 0; k < M_WIDTH; k++)
                    if (mazeMatrix[i][k] == j) indices[count++] = k;

                if (count > 0) {
                    int forced = rand() % count;
                    int base = indices[forced];
                    mazeMatrix[i + 1][base] = j;
                    maze[(i * 2) + 2][(base * 2) + 1] = ' ';

                    for (int d = 0; d < count; d++) {
                        if (d == forced) continue;
                        int P = rand() % 100 + 1;
                        if (P < VERTICAL) {
                            int k = indices[d];
                            mazeMatrix[i + 1][k] = j;
                            maze[(i * 2) + 2][(k * 2) + 1] = ' ';
                        }
                    }
                }
            }
        }
    }
    //Cria a ultima linha unindo tudo que falta, para não gerar becos
    for (int j = 1; j < M_WIDTH; j++) {
        if ((mazeMatrix[M_HEIGHT - 1][j] != mazeMatrix[M_HEIGHT - 1][j - 1])  || (mazeMatrix[M_HEIGHT-1][j] == 0 && mazeMatrix[M_HEIGHT-1][j-1] == 0) ) {
            if (((M_HEIGHT - 1) * 2 + 1) < HEIGHT && (j * 2) < WIDTH)
                maze[(M_HEIGHT - 1) * 2 + 1][j * 2] = ' ';
        }
    }

    //Salva um txt do labirinto, apenas para analises de comportamento
    FILE *arquivo = fopen("labirinto.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (int i = 0; i < M_HEIGHT; i++) {
        for (int j = 0; j < M_WIDTH; j++) {
            fprintf(arquivo, "%d ", mazeMatrix[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}
void clearTrail() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            visited[i][j] = false;
        }
    }
    visited[actor.y][actor.x] = true; // Marca a posição inicial
}

void init() {   //Função que inicia a tela
    WINDOW *win = initscr();
    cbreak();
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    curs_set(0);
    start_color();

    
    randomDoor();
    actor.x = enterDoor.x;    //Define o ator/personagem
    actor.y = enterDoor.y;
    clearTrail();

    //Prepara o labirinto
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                maze[i][j] = '█';
            else if ((i % 2 == 0) || (j % 2 == 0))
                maze[i][j] = '█';
            else 
                maze[i][j] = ' ';
        }
    }
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            if (enterDoor.y == i && enterDoor.x == j)
                maze[i][j] = '+';
            else if (leaveDoor.y == i && leaveDoor.x == j)
                maze[i][j] = '_';
        }
    }
}
