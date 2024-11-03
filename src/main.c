#include <stdlib.h>
#include "ui/board.h"
#include "ui/select-shot-spot.h"

int main(void) {
    system("clear");
    Board bored = newBoard(Shots);
    PrintInfo miss = MISS_PRINT_INFO;
    PrintInfo hit = HIT_PRINT_INFO;
    bored.board[3][3] = miss;
    bored.board[8][2] = hit;
    select_spot(&bored);
}