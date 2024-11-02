#include <stdio.h>
#include "board.h"
#include "coord.h"
#include <stdlib.h>

int main(void) {
    system("clear");
    Board bored;
    BoardFactory(&bored, ShotsBoard);
    bored.print_board(&bored);
}