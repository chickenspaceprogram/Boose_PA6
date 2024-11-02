#include <stdio.h>
#include "ui/board.h"
#include "coord.h"
#include <stdlib.h>
#include "ctty/ansi/cursor.h"

int main(void) {
    system("clear");
    Board bored = newBoard();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        bored.board[i][i].bg_color = BrightRed;
    }
    printf(HIDE_CURSOR);
    bored.print_board(&bored);
    bored.print_symbols(&bored);
    GETCH();
    printf(SHOW_CURSOR);
}