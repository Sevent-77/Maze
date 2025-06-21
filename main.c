#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define M_HEIGHT 15                 //Tamanho da matriz do labirinto
#define M_WIDTH 15                  //Tamanho da matriz do labirinto
#define HEIGHT (2*M_HEIGHT)+1       //Tamanho do labirinto
#define WIDTH (2*M_WIDTH)+1         //Tamanho do labirinto

typedef struct
{
    int x, y, dx, dy, damage, alive;
}Bullet;                            //Struct de bala

typedef struct 
{
    int x, y, damage, alive, life;
} Character;                        //Struct de personagem

char maze[HEIGHT][WIDTH];           //Criando o labirinto
struct timespec lastBulletMove, lastEnemyMove, Now; //Variaveis para guardar o tempo
Character enemys[10];               //Definindo os inimigos
Character actor;                    //Definindo o personagem
Bullet bullets[100];                //Definindo as balas            

void init();                        //Definindo as funções
void show();
void entryProcess();
void mazeGen(int HORIZONTAL, int VERTICAL);
int getElapsedTime(struct timespec *lastEvent, double interval);
void Enemys();
void Bullets();
void firesBullet(int dx, int dy, int x, int y, int damage);
void createEnemy(int x, int y, int damage, int life);
void searchFor(int originX, int originY, int *destX, int *destY, char target);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int HORIZONTAL = rand() % 90 + 1; //Parâmetro de horinzontalidade e de verticalidade
    int VERTICAL = rand() % 2 + 1;
    init();
    mazeGen(HORIZONTAL, VERTICAL);

    while (1) {
        show();                         //loop de execução
        entryProcess();
        Enemys();
        Bullets();
    }
    endwin();
    return 0;
}

void entryProcess() {           //Definir a função para fazer o movimento do personagem
    maze[actor.x][actor.y] = ' ';
    int key = getch();
    switch (key) {
        case KEY_UP:
            if (maze[actor.x - 1][actor.y] == ' ') actor.x--;
            break;
        case KEY_LEFT:
            if (maze[actor.x][actor.y - 1] == ' ') actor.y--;
            break;
        case KEY_DOWN:
            if (maze[actor.x + 1][actor.y] == ' ') actor.x++;
            break;
        case KEY_RIGHT:
            if (maze[actor.x][actor.y + 1] == ' ') actor.y++;
            break;
        case 'w':
            firesBullet(-1, 0, actor.x, actor.y, 1);
            break;
        case 'a':
            firesBullet(0, -1, actor.x, actor.y, 1);
            break;
        case 's':
            firesBullet(1, 0, actor.x, actor.y, 1);
            break;
        case 'd':
            firesBullet(0, 1, actor.x, actor.y, 1);
            break;
    }
    maze[actor.x][actor.y] = 'o';
}

void firesBullet(int dx, int dy, int x, int y, int damage)//Função que dispara bala
{
    if(maze[x + dx][y + dy] != ' ' && maze[x + dx][y + dy] != '.') return;

    for(int i = 0; i < 100; i++) {
        if (!bullets[i].alive) //Encontra a primeira bala livre
        {
            bullets[i].dx = dx;
            bullets[i].dy = dy;
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].damage = damage;
            bullets[i].alive = 1;
            break;
        }
    }
}

void Bullets() //Itera a lista de balas e diz o que cada uma faz
{
    //A função executa a cada quinto de segundo
    if(!getElapsedTime(&lastBulletMove, 0.2)) return;
    
    for(int i = 0; i < 100; i++)
    {
        if(bullets[i].alive == 0) continue;

        maze[bullets[i].x][bullets[i].y] = ' ';

        bullets[i].x += bullets[i].dx;
        bullets[i].y += bullets[i].dy;
        if(maze[bullets[i].x][bullets[i].y] == 'x')
        {
            bullets[i].alive = 0;
            //Busca na lista de inimigos para saber qual inimigo foi atingido
            for(int j = 0; j < 10; j++)
                if(enemys[j].alive && enemys[j].x == bullets[i].x && enemys[j].y == bullets[i].y) 
                    enemys[j].life -= bullets[i].damage;
        }
        else if(maze[bullets[i].x][bullets[i].y] != ' ') 
        {
            bullets[i].alive = 0;
        }
        else
        {
            maze[bullets[i].x][bullets[i].y] = '.';
        }
    }
}

//Função que cria inimigos
void createEnemy(int x, int y, int damage, int life) {
    for (int i = 0; i < 10; i++) 
    {
        if (!enemys[i].alive) 
        {
            enemys[i].x = x;
            enemys[i].y = y;
            enemys[i].damage = damage;
            enemys[i].life = life;
            enemys[i].alive = 1;
            break;
        }
    }
}

void Enemys() //Itera a lista de inimigos e diz o que cada um faz
{
    //A função executa a cada segundo
    //if(!getElapsedTime(&lastEnemyMove, 1.0)) return; Não faz sentido
    //o teste de tempo aqui, pois caso o player mate-o, ele só desaparece no próximo loop
    // melhor colocar o teste de tempo na função de movimento dele

    for(int i = 0; i < 10; i++)
    {
        if(enemys[i].alive == 0) continue;
        if(enemys[i].life <= 0) {
            enemys[i].alive = 0;
            maze[enemys[i].x][enemys[i].y] = ' ';
            continue;
        }

        maze[enemys[i].x][enemys[i].y] = ' ';

        if(getElapsedTime(&lastEnemyMove, 1.0)) //Movimenta o inimigo a cada segundo
        {
            int direction = rand() % 4;
            switch (direction) {
                case 0:
                    if (maze[enemys[i].x - 1][enemys[i].y] == ' ') enemys[i].x--;
                    break;
                case 1:
                    if (maze[enemys[i].x][enemys[i].y - 1] == ' ') enemys[i].y--;
                    break;
                case 2:
                    if (maze[enemys[i].x + 1][enemys[i].y] == ' ') enemys[i].x++;
                    break;
                case 3:
                    if (maze[enemys[i].x][enemys[i].y + 1] == ' ') enemys[i].y++;
                    break;
            }
        }

        maze[enemys[i].x][enemys[i].y] = 'x';
    }
}

void searchFor(int originX, int originY, int *destX, int *destY, char target) //Busca por um alvo no labirinto
{
    //falta implementar
}

int getElapsedTime(struct timespec *lastEvent, double interval) //Calcula o tempo decorrido desde o último evento
{
    clock_gettime(CLOCK_MONOTONIC, &Now);
    double elapsed = (Now.tv_sec - lastEvent->tv_sec) + (Now.tv_nsec - lastEvent->tv_nsec) / 1e9;
    if (elapsed >= interval) {
        *lastEvent = Now;
        return 1;
    }
    return 0;
}

void show() { //Exibe o labirinto na tela
    for (size_t i = 0; i < HEIGHT; i++)
        for (size_t j = 0; j < WIDTH; j++)
            mvaddch(i, j, maze[i][j]);
    refresh();
}

void mazeGen(int HORIZONTAL, int VERTICAL) { //Função que gera o labirinto
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
        if (mazeMatrix[M_HEIGHT - 1][j] != mazeMatrix[M_HEIGHT - 1][j - 1]) {
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

void init() {   //Função que inicia a tela
    WINDOW *win = initscr();
    cbreak();
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    curs_set(0);
    start_color();
    endwin();

    actor.x = 1;    //Define o ator/personagem
    actor.y = 1;

    createEnemy(1, 1, 1, 3);

    //Inicia os eventos de tempo
    clock_gettime(CLOCK_MONOTONIC, &lastEnemyMove);
    clock_gettime(CLOCK_MONOTONIC, &lastBulletMove);

    //Prepara o labirinto
    for (size_t i = 0; i < HEIGHT; i++) {
        for (size_t j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                maze[i][j] = '#';
            else if ((i % 2 == 0) || (j % 2 == 0))
                maze[i][j] = '*';
            else
                maze[i][j] = ' ';
        }
    }
}
