#include <stdlib.h>
#include "ui/board.h"
#include "ui/select-shot-spot.h"

int main(void) {
    system("clear");
    Board bored = newBoard(Shots);
    bored.board[3][3].bg_color = BrightWhite;
    bored.board[3][3].fg_color = Black;
    bored.board[3][3].symbol = 'm';
    bored.board[8][2].bg_color = BrightRed;
    bored.board[8][2].fg_color = BrightWhite;
    bored.board[8][2].symbol = '*';
    select_spot(&bored);
}