#include <stdlib.h>
#include "ui/board.h"
#include "ui/place-ships.h"
#include "ctty/screen/screen.h"
#include "ctty/ansi/cursor.h"
#include "rand.h"

void printship(ShipInfo ship);

int main(void) {
    seed_rand();
    system("clear");
    Board bored = newBoard(Ships);
    ShipInfo ships[5];
    printf(CURSOR_OFF);
    player_place_ships(&bored, ships);
    PAUSE();
    printf(CURSOR_ON);
    system("clear");
    for (int i = 0; i < 5; ++i) {
        printship(ships[i]);
    }
}

void printship(ShipInfo ship) {
    printf("Ship: ");
    switch (ship.ship) {
        case Destroyer:
            printf("Destroyer\n");
            break;
        case Submarine:
            printf("Submarine\n");
            break;
        case Cruiser:
            printf("Cruiser\n");
            break;
        case Battleship:
            printf("Battleship\n");
            break;
        case Carrier:
            printf("Carrier\n");
            break;
    }
    if (ship.position.col == 9) {
        ship.position.col = -1;
    }
    printf("Position: {%c, %c}\n", ship.position.row + 'a', ship.position.col + '1');
    printf("ship_is_hit: ");
    if (ship.ship_is_hit) {
        printf("True\n");
    }
    else {
        printf("False\n");
    }
    printf("Orientation: ");
    if (ship.orientation == Horizontal) {
        printf("Horizontal\n");
    }
    else {
        printf("Vertical\n");
    }
    
}