#include <stdio.h>
#include <time.h>
#include <ncurses.h>

#define HEIGHT 11
#define WIDTH 11

typedef struct
{
    int x, y;
} Position;

void show();
void BFS(Position origin, Position *destiny, char target);
void init();
void movement();

int visited[HEIGHT][WIDTH];
Position queue[HEIGHT * WIDTH];
Position cameFrom[HEIGHT][WIDTH];
char maze[11][11] =
    {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

int main()
{
    WINDOW *win = initscr();
    cbreak();
    nodelay(win, TRUE);
    noecho();
    keypad(win, TRUE);
    curs_set(0);
    start_color();

    init();
    while(1)
    {
        show();
    }
    endwin();
    return 0;
}

void init()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (maze[i][j] == '#')
            {
                visited[i][j] = -1;
            }
        }
    }
}

void show()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            mvaddch(i, j, maze[i][j]);
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (visited[i][j] == -1)
            {
                mvprintw(i + HEIGHT + 1, j, "# ");
            }
            else
            {
                mvprintw(i + HEIGHT + 1, j, "%d ", visited[i][j]);
            }
        }
    }
    refresh();
}

void movement()
{
}

void BFS(Position origin, Position *destiny, char target)   
{
    if (maze[origin.y][origin.x] == target)
    {
        destiny->y = 0;
        destiny->x = 0;
    }
    visited[origin.y][origin.x] = 1;

    int start = 0, end = 0;

    Position direction[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++)
    {
        Position Node = {origin.y + direction[i].y, origin.x + direction[i].x};

        if (validPostionBFS(Node, target))
        {
            enqueue(Node, &end);
            visited[Node.y][Node.x] = 1;
            cameFrom[Node.y][Node.x] = origin;
        }
    }

    Position CurrentN;

    while (start < end)
    {
        CurrentN = dequeue(&start);

        if(maze[CurrentN.y][CurrentN.x] == target)
        {
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            Position Node = {CurrentN.y + direction[i].y, CurrentN.x + direction[i].x};

            if (validPostionBFS(Node, target))
            {
                enqueue(Node, &end);
                visited[Node.y][Node.x] = 1;
                cameFrom[Node.y][Node.x] = CurrentN;
            }
        }
    }

    //fiz assim porque não quero criar uma função que compara struct
    while(maze[cameFrom[CurrentN.y]->y][cameFrom[CurrentN.x]->x] != maze[origin.y][origin.x])
    {
        CurrentN = cameFrom[CurrentN.y][CurrentN.x];
    }

    destiny->y = CurrentN.y - origin.y;
    destiny->x = CurrentN.x - origin.x;
}

void enqueue(Position value, int *end) //adciona na fila
{
    queue[*end] = value;
    (*end)++;
}

Position dequeue(int *start) //tira da fila
{
    Position p = queue[*start];
    (*start)++;
    return p;
}

int validPostionBFS(Position value, char target) //verifica se a posição é valida para o BFS
{
    if ((maze[value.y][value.x] == ' ' || maze[value.y][value.x] == target) && visited[value.y][value.x] == 0)
        return 1;
    else
        return 0;
}