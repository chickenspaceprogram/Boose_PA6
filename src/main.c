#include <stdlib.h>
#include "ui/board.h"
#include "ui/place-ships.h"


int main(void) {
    system("clear");
    Board bored = newBoard(Ships);
    printf(HIDE_CURSOR);
    place_ships(&bored);
    printf(SHOW_CURSOR);
}