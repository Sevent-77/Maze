#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
<<<<<<< HEAD

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
=======
#include <string.h>

#define M_HEIGHT 20               // Tamanho da matriz do labirinto
#define M_WIDTH 20                // Tamanho da matriz do labirinto
#define HEIGHT (2 * M_HEIGHT) + 1 // Tamanho do labirinto
#define WIDTH (2 * M_WIDTH) + 1   // Tamanho do labirinto

typedef struct
{
    int y, x; // Struct de objeto
} Coordinates;

typedef struct
{
    int interval, alive, entranceTime;
    Coordinates position;
    struct timespec lastEvent;
    char object;
} Character;

Coordinates enterDoor;
Coordinates leaveDoor;
Character actor;   // Definindo o personagem
Character stalker; // Definindo o perseguidor

struct timespec Now, lastMazeGen;
char maze[HEIGHT][WIDTH];              // Criando o labirinto
bool trail_active = false;             // Controle do rastro (ativar/desativar)
bool sleep_active = false;             // Controle do rastro (ativar/desativar)
bool visited[HEIGHT][WIDTH] = {false}; // Rastrear posições visitadas
int visitedPosition[HEIGHT][WIDTH] = {{0}};
int visitedBFS[HEIGHT][WIDTH];
Coordinates queue[100000000];
Coordinates cameFrom[HEIGHT][WIDTH];
int HORIZONTAL;
int VERTICAL;

void init(); // Definindo as funções
>>>>>>> main
void show();
void entryProcess();
void mazeGen();
void clearTrail();
void randomDoor();
void genNewMaze();
<<<<<<< HEAD

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
=======
int getElapsedTime(struct timespec *lastEvent, double interval);
void Stalker();
void createStalker(int x, int y);
void searchFor(int originX, int originY, int *destX, int *destY, char target);
int validPostionBFS(Coordinates value, char target);
Coordinates dequeue(int *start);
void enqueue(Coordinates value, int *end);
void BFS(Coordinates origin, Coordinates *destiny, char target);
void initBFS();

int main()
{
    srand(time(NULL));
    HORIZONTAL = rand() % 100 + 1; // Parâmetro de horinzontalidade e de verticalidade
    VERTICAL = rand() % 100 + 1;
    init();
    mazeGen();

    // randomDoor();
    int p = 0;
    Coordinates l = {0,0};
    while (1)
    {
        show(); // loop de execução
        entryProcess();
        Stalker();
>>>>>>> main
    }
    endwin();
    return 0;
}
<<<<<<< HEAD
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
=======

void genNewMaze()
{
    clearTrail();                  // Limpa o rastro
    HORIZONTAL = rand() % 100 + 1; // Reinicializa parâmetros e gera novo labirinto
    VERTICAL = rand() % 100 + 1;
    init();
    mazeGen();
    clock_gettime(CLOCK_MONOTONIC, &lastMazeGen);
}

void randomDoor()
{
    int entryWall = rand() % 4 + 1;
    int exitWall = 0;

    while (1)
    {
>>>>>>> main
        exitWall = rand() % 4 + 1;
        if (entryWall != exitWall)
            break;
    }

    // Entrada
<<<<<<< HEAD
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
=======
    switch (entryWall)
    {
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
    switch (exitWall)
    {
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
>>>>>>> main
    }

    // maze[enterDoor.y][enterDoor.x] = ' ';
    // maze[leaveDoor.y][leaveDoor.x] = ' ';
}

<<<<<<< HEAD

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
=======
void entryProcess()
{
    maze[actor.position.y][actor.position.x] = ' ';
    int key = getch();
    switch (key)
    {
    case KEY_UP:
        if (maze[actor.position.y - 1][actor.position.x] == ' ')
        {
            visited[actor.position.y][actor.position.x] = true; // Marca posição atual
            actor.position.y--;
        }
        else if (maze[actor.position.y - 1][actor.position.x] == '_')
        {
            genNewMaze();
        }
        break;
    case KEY_LEFT:
        if (maze[actor.position.y][actor.position.x - 1] == ' ')
        {
            visited[actor.position.y][actor.position.x] = true;
            actor.position.x--;
        }
        else if (maze[actor.position.y][actor.position.x - 1] == '_')
        {
            genNewMaze();
        }
        break;
    case KEY_DOWN:
        if (maze[actor.position.y + 1][actor.position.x] == ' ')
        {
            visited[actor.position.y][actor.position.x] = true;
            actor.position.y++;
        }
        else if (maze[actor.position.y + 1][actor.position.x] == '_')
        {
            genNewMaze();
        }
        break;
    case KEY_RIGHT:
        if (maze[actor.position.y][actor.position.x + 1] == ' ')
        {
            visited[actor.position.y][actor.position.x] = true;
            actor.position.x++;
        }
        else if (maze[actor.position.y][actor.position.x + 1] == '_')
        {
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
    case 'z':
        sleep_active = !sleep_active;
        break;
    }

    maze[actor.position.y][actor.position.x] = 'o';
}

void createStalker(int x, int y) // Função que cria o stalker
{
    if(!getElapsedTime(&lastMazeGen, stalker.entranceTime)) return;
    if (stalker.alive == 0)
    {
        stalker.interval = 1.0;
        clock_gettime(CLOCK_MONOTONIC, &stalker.lastEvent);
        stalker.object = 'x';
        stalker.alive = 1;
        stalker.position.y = enterDoor.y;
        stalker.position.x = enterDoor.x;
    }
}

void Stalker()
{
    if(!getElapsedTime(&stalker.lastEvent, 0.2)) 
    {
        return;
    }
    Coordinates d = {0,0};
    BFS(stalker.position, &d, 'o');
        stalker.position.y += d.y;
        stalker.position.x += d.x;
}

void initBFS()
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            cameFrom[i][j].y = 0;
            cameFrom[i][j].x = 0;
            visitedBFS[i][j] = 0;
        }
    }

    for(int i = 0; i < HEIGHT * WIDTH * 2; i++)
    {
        queue[i].y = 0;
        queue[i].x = 0;
    }
}

void BFS(Coordinates origin, Coordinates *destiny, char target) // Algoritmo de Breadth First Search
{
    mvprintw(2*HEIGHT+1, 2*WIDTH+1, "%d, %d e %d, %d", actor.position.y, actor.position.x, stalker.position.y, stalker.position.x);
    refresh();
    // usleep(250000);

    if((actor.position.y <= 0 || actor.position.y >= HEIGHT || actor.position.x <= 0 || actor.position.x >= WIDTH) || (stalker.position.y == actor.position.y && stalker.position.x == actor.position.x))
    {
        mvprintw(HEIGHT+11, 0, "If 1 executado");
        refresh();
        return;
    }

    int start = 0, end = 0;
    Coordinates direction[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    visitedBFS[origin.y][origin.x] = 1;
    initBFS();

    mvprintw(origin.y, origin.x+WIDTH, "c");
    for (int i = 0; i < 4; i++)
    {
        Coordinates Node = {origin.y + direction[i].y, origin.x + direction[i].x};

        mvprintw(origin.y, origin.x+WIDTH, "c");
        if (validPostionBFS(Node, target))
        {
            mvprintw(Node.y, Node.x+WIDTH, "v");
            enqueue(Node, &end);
            visitedBFS[Node.y][Node.x] = 1;
            cameFrom[Node.y][Node.x] = origin;
        }
    }
    

    Coordinates CurrentN;
    for (size_t i = 0; i < HEIGHT; i++) {
    move(i, WIDTH);            // Posiciona cursor no início da linha
    clrtoeol();                // Limpa até o final da linha - mais eficiente
}
    

    while (start < end)
    {
        if (sleep_active)
        {
            usleep(50000);
        }
        CurrentN = dequeue(&start);

        if (CurrentN.y == actor.position.y && CurrentN.x == actor.position.x)
        {
            break;
        }

        mvprintw(CurrentN.y, CurrentN.x+WIDTH, "c");

        for (int i = 0; i < 4; i++)
        {
            Coordinates Node = {CurrentN.y + direction[i].y, CurrentN.x + direction[i].x};

            if (validPostionBFS(Node, target))
            {
                mvprintw(Node.y, Node.x+WIDTH, "v");
                mvprintw(0, 3*WIDTH + 1, "posicao valida: %d, %d", Node.y, Node.x);
                enqueue(Node, &end);
                visitedBFS[Node.y][Node.x] = 1;
                cameFrom[Node.y][Node.x] = CurrentN;
            }
            refresh();
        }
    }

    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
        {
            mvprintw(1+i, 2 * WIDTH + j * 7, "|%d, %d", cameFrom[i][j].y, cameFrom[i][j].x);
        }
    refresh();

    int try = 0;
    // fiz assim porque não quero criar uma função que compara struct
    while (cameFrom[CurrentN.y][CurrentN.x].y != origin.y || cameFrom[CurrentN.y][CurrentN.x].x != origin.x)
    {
        mvprintw(HEIGHT + 7 + CurrentN.y, 0 + CurrentN.x,"i");
        CurrentN = cameFrom[CurrentN.y][CurrentN.x];
        try++;
        if(try >= HEIGHT * WIDTH * 10)
        {
            destiny->y = 0;
            destiny->x = 0;
            return;
        }
    }

    destiny->y = CurrentN.y - origin.y;
    destiny->x = CurrentN.x - origin.x;
}

void enqueue(Coordinates value, int *end) // adciona na fila
{
    queue[*end] = value;
    (*end)++;
}

Coordinates dequeue(int *start) // tira da fila
{
    Coordinates p = queue[*start];
    (*start)++;
    return p;
}

int validPostionBFS(Coordinates value, char target) // verifica se a posição é valida para o BFS
{
    if (visitedBFS[value.y][value.x] == 0 && (maze[value.y][value.x] == ' ' || maze[value.y][value.x] == target))
        return 1;
    else
        return 0;
}

int getElapsedTime(struct timespec *lastEvent, double interval) // Calcula o tempo decorrido desde o último evento
{
    clock_gettime(CLOCK_MONOTONIC, &Now);
    double elapsed = (Now.tv_sec - lastEvent->tv_sec) + (Now.tv_nsec - lastEvent->tv_nsec) / 1e9;
    if (elapsed >= interval)
    {
        *lastEvent = Now;
        return 1;
    }
    return 0;
}

void show()
{
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (i == actor.position.y && j == actor.position.x)
            {
                mvaddch(i, j, 'o');
            }
            else if (i == stalker.position.y && j == stalker.position.x)
            {
                mvaddch(i, j, 'x');
            }
            else if (i == enterDoor.y && j == enterDoor.x)
            {
                mvaddch(i, j, '+');
            }
            else if (i == leaveDoor.y && j == leaveDoor.x)
            {
                mvaddch(i, j, '_');
            }
            else if (trail_active && visited[i][j] && maze[i][j] == ' ')
            {
                mvaddch(i, j, '.'); // Exibe rastro
            }
            else
            {
>>>>>>> main
                mvaddch(i, j, maze[i][j]);
            }
        }
    }
    // Exibe status do rastro
<<<<<<< HEAD
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
=======
    mvprintw(HEIGHT + 1, 0, "Rastro: %s (T para alternar)",
             trail_active ? "ATIVO  " : "INATIVO");
    mvprintw(HEIGHT + 2, 0, "Horizontal: %d", HORIZONTAL);
    mvprintw(HEIGHT + 3, 0, "Vertical: %d", VERTICAL);
    mvprintw(HEIGHT + 4, 0, "X: %d Y: %d", enterDoor.x, enterDoor.y);
    mvprintw(HEIGHT + 5, 0, "X: %d Y: %d", leaveDoor.x, leaveDoor.y);
    mvprintw(HEIGHT + 6, 0, "Sleep: %s (Z para alternar)",
             sleep_active ? "ATIVO  " : "INATIVO");
    mvprintw(HEIGHT+1, 2*WIDTH+1, "%d, %d e %d, %d", actor.position.y, actor.position.x, stalker.position.y, stalker.position.x);
    refresh();
}

void mazeGen()
{
    int number = 1;
    int mazeMatrix[M_HEIGHT + 1][M_WIDTH]; // Cria a matriz

    // Limpa a matriz definindo tudo para 0
>>>>>>> main
    for (int i = 0; i < M_HEIGHT; i++)
        for (int j = 0; j < M_WIDTH; j++)
            mazeMatrix[i][j] = 0;

<<<<<<< HEAD
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
=======
    for (int i = 0; i < M_HEIGHT - 1; i++)
    {
        // Cria um array para armazenar o numero de vezes que um número aparece
        int arr[M_WIDTH * M_WIDTH] = {0};

        // Cria a matrix que de suporte para o labirinto
        for (int j = 0; j < M_WIDTH; j++)
            if (mazeMatrix[i][j] == 0)
                // Adiciona o numero a matriz
                mazeMatrix[i][j] = number++;

        // Une conjuntos usando o parâmetro de aleatoriedade
        for (int j = 1; j < M_WIDTH; j++)
        {
            int N = rand() % 100 + 1;
            if (N < HORIZONTAL && mazeMatrix[i][j] != mazeMatrix[i][j - 1])
            {
>>>>>>> main
                int oldSet = mazeMatrix[i][j];
                int newSet = mazeMatrix[i][j - 1];
                for (int k = 0; k < M_WIDTH; k++)
                    if (mazeMatrix[i][k] == oldSet)
                        mazeMatrix[i][k] = newSet;
            }
        }

<<<<<<< HEAD
        //Se vários elementos são de um mesmo conjunto, eles são unidos
=======
        // Se vários elementos são de um mesmo conjunto, eles são unidos
>>>>>>> main
        for (int k = 1; k < M_WIDTH; k++)
            if (mazeMatrix[i][k] == mazeMatrix[i][k - 1])
                maze[i * 2 + 1][k * 2] = ' ';

<<<<<<< HEAD
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
=======
        // Adiciona os conjuntos ao vetor
        for (int j = 0; j < M_WIDTH; j++)
            arr[mazeMatrix[i][j]]++;

        // Verifica o vetor inteirto para ver se o grupo ira se unir com a próxima linha
        for (int j = 0; j < M_WIDTH * M_WIDTH; j++)
        {
            if (arr[j] == 0)
                continue;
            // Se só tiver 1 elemento, com certeza vai se unir
            if (arr[j] == 1)
            {
                for (int k = M_WIDTH - 1; k >= 0; k--)
                {
                    if (mazeMatrix[i][k] == j && i < M_HEIGHT - 1)
                    {
>>>>>>> main
                        mazeMatrix[i + 1][k] = j;
                        maze[(i * 2) + 2][(k * 2) + 1] = ' ';
                        break;
                    }
                }
<<<<<<< HEAD
            
            } else {    //Se tiver mais de um, aleatoriamente vai juntar ou não
                int indices[M_WIDTH], count = 0;
                for (int k = 0; k < M_WIDTH; k++)
                    if (mazeMatrix[i][k] == j) indices[count++] = k;

                if (count > 0) {
=======
            }
            else
            { // Se tiver mais de um, aleatoriamente vai juntar ou não
                int indices[M_WIDTH], count = 0;
                for (int k = 0; k < M_WIDTH; k++)
                    if (mazeMatrix[i][k] == j)
                        indices[count++] = k;

                if (count > 0)
                {
>>>>>>> main
                    int forced = rand() % count;
                    int base = indices[forced];
                    mazeMatrix[i + 1][base] = j;
                    maze[(i * 2) + 2][(base * 2) + 1] = ' ';

<<<<<<< HEAD
                    for (int d = 0; d < count; d++) {
                        if (d == forced) continue;
                        int P = rand() % 100 + 1;
                        if (P < VERTICAL) {
=======
                    for (int d = 0; d < count; d++)
                    {
                        if (d == forced)
                            continue;
                        int P = rand() % 100 + 1;
                        if (P < VERTICAL)
                        {
>>>>>>> main
                            int k = indices[d];
                            mazeMatrix[i + 1][k] = j;
                            maze[(i * 2) + 2][(k * 2) + 1] = ' ';
                        }
                    }
                }
            }
        }
    }
<<<<<<< HEAD
    //Cria a ultima linha unindo tudo que falta, para não gerar becos
    for (int j = 1; j < M_WIDTH; j++) {
        if ((mazeMatrix[M_HEIGHT - 1][j] != mazeMatrix[M_HEIGHT - 1][j - 1])  || (mazeMatrix[M_HEIGHT-1][j] == 0 && mazeMatrix[M_HEIGHT-1][j-1] == 0) ) {
=======
    // Cria a ultima linha unindo tudo que falta, para não gerar becos
    for (int j = 1; j < M_WIDTH; j++)
    {
        if ((mazeMatrix[M_HEIGHT - 1][j] != mazeMatrix[M_HEIGHT - 1][j - 1]) || (mazeMatrix[M_HEIGHT - 1][j] == 0 && mazeMatrix[M_HEIGHT - 1][j - 1] == 0))
        {
>>>>>>> main
            if (((M_HEIGHT - 1) * 2 + 1) < HEIGHT && (j * 2) < WIDTH)
                maze[(M_HEIGHT - 1) * 2 + 1][j * 2] = ' ';
        }
    }

<<<<<<< HEAD
    //Salva um txt do labirinto, apenas para analises de comportamento
    FILE *arquivo = fopen("labirinto.txt", "w");
    if (arquivo == NULL) {
=======
    // Salva um txt do labirinto, apenas para analises de comportamento
    FILE *arquivo = fopen("labirinto.txt", "w");
    if (arquivo == NULL)
    {
>>>>>>> main
        printf("Erro ao criar o arquivo.\n");
        return;
    }

<<<<<<< HEAD
    for (int i = 0; i < M_HEIGHT; i++) {
        for (int j = 0; j < M_WIDTH; j++) {
=======
    for (int i = 0; i < M_HEIGHT; i++)
    {
        for (int j = 0; j < M_WIDTH; j++)
        {
>>>>>>> main
            fprintf(arquivo, "%d ", mazeMatrix[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}
<<<<<<< HEAD
void clearTrail() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            visited[i][j] = false;
        }
    }
    visited[actor.y][actor.x] = true; // Marca a posição inicial
}

void init() {   //Função que inicia a tela
=======

void clearTrail()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            visited[i][j] = false;
        }
    }
    visited[actor.position.y][actor.position.x] = true; // Marca a posição inicial
}

void init()
{ // Função que inicia a tela
>>>>>>> main
    WINDOW *win = initscr();
    cbreak();
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    curs_set(0);
    start_color();

<<<<<<< HEAD
    
    randomDoor();
    actor.x = enterDoor.x;    //Define o ator/personagem
    actor.y = enterDoor.y;
    clearTrail();

    //Prepara o labirinto
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
=======
    randomDoor();
    actor.position.x = enterDoor.x; // Define o ator/personagem
    actor.position.y = enterDoor.y;
    clearTrail();
    stalker.entranceTime = 5.0;
    stalker.position.x = enterDoor.x;
    stalker.position.y = enterDoor.y;

    // Prepara o labirinto
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
>>>>>>> main
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                maze[i][j] = '█';
            else if ((i % 2 == 0) || (j % 2 == 0))
                maze[i][j] = '█';
<<<<<<< HEAD
            else 
                maze[i][j] = ' ';
        }
    }
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
=======
            else
                maze[i][j] = ' ';
        }
    }
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
>>>>>>> main
            if (enterDoor.y == i && enterDoor.x == j)
                maze[i][j] = '+';
            else if (leaveDoor.y == i && leaveDoor.x == j)
                maze[i][j] = '_';
        }
    }
}
