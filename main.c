#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define M_HEIGHT 6
#define M_WIDTH 6
#define VERTICAL 30
#define HORIZONTAL 50
#define HEIGHT (2*M_HEIGHT)+1
#define WIDTH (2*M_WIDTH)+1


char maze[HEIGHT][WIDTH];
void init();
void show();
void mazeGen();

int main()
{
    srand(time(NULL));
    init();
    mazeGen();
    show();
    return 0;
}

void show(){
    for (size_t i = 1; i < HEIGHT - 1; i++)
    {
        for (size_t j = 1; j < WIDTH - 1; j++)
        {
            //maze[i][j] = ' ';
        }
    }
    
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (maze[i][j] == '#')
            {
                mvaddch(i, j, maze[i][j]);
            }else if(maze[i][j] == '+')
            {
                mvaddch(i, j, maze[i][j]);
            }
            else{
                mvaddch(i, j, maze[i][j]);
            }
        }
    }
    refresh();
}
void mazeGen(){
    int number = 1;
    int mazeMatrix[M_HEIGHT+1][M_WIDTH];
    
    for (size_t i = 0; i < M_HEIGHT; i++)
    {
        for (size_t j = 0; j < M_WIDTH; j++)
        {
            mazeMatrix[i][j] = 0;                 //Limpando Matriz antes de começar
        }
    }
    for (size_t i = 0; i < M_HEIGHT; i++)
    {
        int arr[M_WIDTH*M_WIDTH] = {0};
        for (size_t j = 0; j < M_WIDTH; j++)
        { 
            if (mazeMatrix[i][j] == 0)
            {
                mazeMatrix[i][j] = number++;      //Adicionando Números
            }
        }
        for (size_t j = 1; j < M_WIDTH; j++)      //Randomizando conjuntos e juntando eles
        {
            int N = rand() % 100+1;
            if (N < HORIZONTAL && mazeMatrix[i][j] != mazeMatrix[i][j-1])
            {
                int oldSet = mazeMatrix[i][j];
                int newSet = mazeMatrix[i][j-1];     

                for (size_t k = 0; k < M_WIDTH; k++)
                {
                    if (mazeMatrix[i][k] == oldSet)
                    {
                        mazeMatrix[i][k] = newSet;
                    }
                }
            
            }
            for (size_t k = 1; k < M_WIDTH; k++)  //Unindo horizontalmente
            {
                if (mazeMatrix[i][k] == mazeMatrix[i][k-1])
                {
                    maze[i*2+1][k*2] = ' ';
                }
                
            }
        }
        
        for (int j = 0; j < M_WIDTH; j++) {
            arr[mazeMatrix[i][j]]++;              //Guardando aparições de números
        }
        for (int j = 0; j < M_WIDTH * M_WIDTH; j++) {
            //printf("%d ",arr[j]);
        }
        //printf("\n\n");
        for (int j = 0; j < M_WIDTH * M_WIDTH; j++) {       //Verificando número de aparições de conjuntos
            int y = arr[j];
            if (y == 0)                           
            {
                continue;
            }else if(y == 1)
            {
                for (size_t k = 0; k < M_WIDTH; k++)
                {
                    if(mazeMatrix[i][k] == j){
                        mazeMatrix[i+1][k] = j;
                        if (i!=(M_HEIGHT-1))
                        {
                            maze[(i*2)+2][(k*2)+1] = ' ';
                        }
                        //printf("%d ",mazeMatrix[i][k]);
                    }
                    
                }
                
            }else if(y > 1){
                int k;
                for (k = 0; k < M_WIDTH; k++)
                {
                    if(mazeMatrix[i][k] == j){
                        break;
                    }
                };
                if(mazeMatrix[i][k] == j){
                    int M = rand() % arr[j];
                    mazeMatrix[i+1][k+M] = j;
                    if (i!=(M_HEIGHT-1))
                    {
                        maze[(i*2)+2][((k+M)*2)+1] = ' ';
                    }
                    //printf("%d ",mazeMatrix[i][k]);
                }
            }
        }
        //printf("\n\n");
    }
    FILE *arquivo = fopen("labirinto.txt", "w");            //Salvando arquivo para fácil leitura
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

void init(){
    WINDOW *win = initscr();
    cbreak();
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    curs_set(0);
    start_color();

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT -1 || j == 0 || j == WIDTH -1)
            {
                maze[i][j] = '#';
            }else if((i % 2 == 0) || (j % 2 == 0))
            {
                maze[i][j] = '*';
            }else
            {
            maze[i][j] = ' ';
            }
        }
    }
}