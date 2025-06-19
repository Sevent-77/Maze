#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define M_HEIGHT 6
#define M_WIDTH 6
#define VERTICAL 60
#define HORIZONTAL 60
#define HEIGHT (2*M_HEIGHT)+1
#define WIDTH (2*M_WIDTH)+1


char maze[HEIGHT][WIDTH];
void init();
void show();
void mazeGen();

int main()
{
    srand(time(NULL));
    //init();
    //show();
    mazeGen();
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
    int mazeMatrix[M_HEIGHT+1][M_WIDTH];
    for (size_t i = 0; i < M_HEIGHT; i++)
    {
        for (size_t j = 0; j < M_WIDTH; j++)
        {
            mazeMatrix[i][j] = 0;
        }
    }
    for (size_t i = 0; i < M_HEIGHT; i++)
    {
        for (size_t j = 0; j < M_WIDTH; j++)
        {
            mazeMatrix[i][j] = j+1;
        }
        for (size_t j = 1; j < M_WIDTH; j++)
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
        }
        
    }
    for (size_t i = 0; i < M_HEIGHT; i++)
    {
        for (size_t j = 0; j < M_WIDTH; j++)
        {
            printf("%d ",mazeMatrix[i][j]);
        }
        printf("\n");
    }
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