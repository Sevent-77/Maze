#define _XOPEN_SOURCE_EXTENDED 1  // Habilita suporte a caracteres largos
#include <locale.h>
#include <wchar.h>                // Para wchar_t
#include <ncursesw/ncurses.h>     // Versão wide do ncurses

int main() {
    setlocale(LC_ALL, "");        // Configura localização para UTF-8
    
    initscr();                    // Inicializa ncurses
    cbreak();
    noecho();

    wchar_t simbolo = 0x2580;     // Caveira Unicode (☠)
    
    // Cria uma string wide terminada em nulo
    wchar_t ws[2] = { simbolo, L'\0' };
    mvaddwstr(0, 0, ws);          // Exibe o caractere
    
    refresh();
    getch();
    endwin();
    
    return 0;
}