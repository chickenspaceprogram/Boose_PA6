#include <stdio.h>
#include "board.h"
#include "coord.h"
#include <stdlib.h>

int main(void) {
    system("clear");
    Board bored = newBoard();
    bored.print_board(&bored);
    GETCH();
}