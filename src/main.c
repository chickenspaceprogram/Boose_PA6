#include <stdlib.h>
#include "ui/board.h"
#include "ui/place-ships.h"
#include "ctty/screen/screen.h"
#include "ctty/ansi/cursor.h"
#include "rand.h"
#include "ctty/menu/menu.h"
#include "ui/select-shot-spot.h"

void printship(ShipInfo ship);

int main(void) {
    seed_rand();
    CLEAR_SCREEN();
    Board bored = newBoard(Ships);
    ShipInfo ships[5];
    printf(CURSOR_OFF);
    place_ships(&bored, ships);
    PAUSE();
    CLEAR_SCREEN();
    Board twobored = newBoard(Shots);
    twobored.board[2][2] = set_hit_print_info(twobored.board[2][2]);
    select_spot(&twobored);


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